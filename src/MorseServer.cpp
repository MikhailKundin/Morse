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

MorseServer::MorseServer(QString configFullName, QObject *parent) 
	: HttpRequestHandler(parent)
{
	// Загрузка настроек сервера
	QSettings* listenerSettings = new QSettings(configFullName, QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
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
	
	qInfo("Settings loaded");
	
	// Сопоставление страницы и контроллера
	controllers.insert("/sign-up", new RegistrationController(this));
	controllers.insert("/sign-in", new AuthenticationController(this));
	controllers.insert("/main", new MainController(this));
	
	// Заполнение списка типов статических файлов
	staticList.append(".css");
	staticList.append(".js");
	staticList.append(".png");
	staticList.append(".jpg");
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
		return controller->requestHandler(request, response);
	}
	
	// Если нужный контроллер не найден, то проверка на запрос статических файлов
	for (int i = 0; i < staticList.size(); i++)
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
