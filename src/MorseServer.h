#ifndef MORSESERVER_H
#define MORSESERVER_H

#include <QHash>

#include "httprequesthandler.h"

using namespace stefanfrings;

class MorseServer : public HttpRequestHandler
{
public:
	MorseServer(QString configFullName, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
};

#endif // MORSESERVER_H
