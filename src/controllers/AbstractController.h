#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "httprequesthandler.h"
#include "../Global.h"

using namespace stefanfrings;

class AbstractController : public QObject
{
public:
	AbstractController(QObject* parent = nullptr);
	virtual void requestHandler(HttpRequest& request, HttpResponse& response) = 0;
	virtual ~AbstractController() = default;
};

#endif // ABSTRACTCONTROLLER_H
