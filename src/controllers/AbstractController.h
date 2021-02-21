#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class AbstractController
{
public:
	virtual void requestHandler(HttpRequest& request, HttpResponse& response) = 0;
	virtual ~AbstractController() = default;
};

#endif // ABSTRACTCONTROLLER_H
