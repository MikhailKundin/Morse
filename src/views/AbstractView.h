#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class AbstractView : public QObject
{
public:
	AbstractView(QObject* parent = nullptr);
	virtual ~AbstractView() = default;
	
	virtual void service(HttpRequest& request, HttpResponse& response) = 0;
};

#endif // ABSTRACTVIEW_H
