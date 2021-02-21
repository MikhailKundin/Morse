#include "MorseServer.h"

#include "httplistener.h"

MorseServer::MorseServer(QString configFullName, QObject *parent) : HttpRequestHandler(parent)
{
	// Загрузка настроек сервера
	QSettings* listenerSettings = new QSettings(configFullName, QSettings::IniFormat);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings, this, this);
	
	
}

void MorseServer::service(HttpRequest &request, HttpResponse &response)
{
	
}
