#include "MorseServer.h"

#include "httplistener.h"
#include "Global.h"

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
    sessionStore = new HttpSessionStore(staticSettings, this);
	
	// Загрузка настроек шаблонов
	QSettings* templateSettings = new QSettings(configFullName, QSettings::IniFormat, this);
    templateSettings->beginGroup("templates");
    templateCache = new TemplateCache(templateSettings, this);
	
	// Загрузка настроек лога
//	QSettings* loggerSettings = new QSettings(configFullName, QSettings::IniFormat, this);
//    loggerSettings->beginGroup("logging");
//    fileLogger = new FileLogger(loggerSettings, 10000, this);
//	fileLogger->installMsgHandler();
	
	qDebug("Settings loaded");
}

void MorseServer::service(HttpRequest &request, HttpResponse &response)
{
	
}
