#ifndef MORSESERVER_H
#define MORSESERVER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class AbstractController;

class MorseServer : public HttpRequestHandler
{
public:
	MorseServer(QString configFullName, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	QHash<QString, AbstractController*> controllers;
	QList<QString> staticList;
};

#endif // MORSESERVER_H
