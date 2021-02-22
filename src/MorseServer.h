#ifndef MORSESERVER_H
#define MORSESERVER_H

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "templatecache.h"
#include "filelogger.h"
#include "Database.h"

using namespace stefanfrings;

extern HttpSessionStore* sessionStore;
extern StaticFileController* staticFileController;
extern TemplateCache* templateCache;
extern FileLogger* fileLogger;
extern Database* database;

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
