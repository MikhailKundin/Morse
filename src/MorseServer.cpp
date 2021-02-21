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
	
	
}

void MorseServer::service(HttpRequest &request, HttpResponse &response)
{
	
}
