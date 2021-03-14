#include "MorseServer.h"

#include "httplistener.h"
#include "controllers/AbstractController.h"
#include "controllers/RegistrationController.h"
#include "controllers/AuthenticationController.h"
#include "controllers/MainController.h"

HttpSessionStore* sessionStore;
StaticFileController* staticFileController;
TemplateCache* templateCache;
FileLogger* fileLogger;
Database* database;

MorseServer::MorseServer(QString configFullName, QObject *parent) 
	: HttpRequestHandler(parent)
{
	// Загрузка настроек сервера
	QSettings* listenerSettings = new QSettings(configFullName, QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
	QByteArray domain = listenerSettings->value("host").toByteArray();
	qint32 port = listenerSettings->value("port").toInt();	
    new HttpListener(listenerSettings, this, this);
	
	// Загрука настроек сессий
	QSettings* sessionSettings = new QSettings(configFullName, QSettings::IniFormat, this);
    listenerSettings->beginGroup("sessions");
    sessionStore = new HttpSessionStore(sessionSettings, this);
	
	// Загрузка настроек сатических файлов
	QSettings* staticSettings = new QSettings(configFullName, QSettings::IniFormat, this);
    staticSettings->beginGroup("static");
    staticFileController = new StaticFileController(staticSettings, this);
	
	// Загрузка настроек шаблонов
	QSettings* templateSettings = new QSettings(configFullName, QSettings::IniFormat, this);
    templateSettings->beginGroup("templates");
    templateCache = new TemplateCache(templateSettings, this);
	
	// Загрузка настроек лога
//	QSettings* loggerSettings = new QSettings(configFullName, QSettings::IniFormat, this);
//    loggerSettings->beginGroup("logging");
//    fileLogger = new FileLogger(loggerSettings, 10000, this);
//	fileLogger->installMsgHandler();
	
	// Загрузка настроек базы данных
	QSettings* databaseSettings = new QSettings(configFullName, QSettings::IniFormat, this);
	databaseSettings->beginGroup("database");
	database = new Database(databaseSettings, this);
	
	qInfo("Settings loaded");
	
	// Сопоставление страницы и контроллера
	controllers.insert("/sign-up", new RegistrationController(domain, port, this));
	controllers.insert("/sign-in", new AuthenticationController(domain, port, this));
	controllers.insert("/main", new MainController(domain, port, this));
	
	// Заполнение списка типов статических файлов
	staticList.append(".css");
	staticList.append(".js");
	staticList.append(".png");
	staticList.append(".jpg");
	
	qInfo("Server is running");
}

void MorseServer::service(HttpRequest &request, HttpResponse &response)
{
	QString path = request.getPath();
	
	// Если путь заканчивается на "/", то удаление этого символа
	if (path.endsWith("/"))
	{
		path.remove(path.size()-1, 1);
	}
	
	// Передача управления нужному контроллеру
	AbstractController* controller = controllers.value(path);
	if (controller != nullptr)
	{
		return controller->service(request, response);
	}
	
	// Если нужный контроллер не найден, то проверка на запрос статических файлов
	for (quint8 i = 0; i < staticList.size(); i++)
	{
		if (path.endsWith(staticList.at(i)))
		{
			return staticFileController->service(request, response);
		}
	}
	
	// Если запрашивались не статические файлы, то была допущена ошибка в пути.
	response.setStatus(404, "Not found");
	response.write(qPrintable(QString::fromUtf8("404: Страница не найдена")));
}
