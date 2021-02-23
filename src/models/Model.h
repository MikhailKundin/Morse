#ifndef MODEL_H
#define MODEL_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class Model : public QObject
{
public:
	Model(QObject* parent = nullptr);
	virtual bool isAuthorized(HttpRequest& request, HttpResponse& response);
	virtual void updateKey(HttpRequest& request, HttpResponse& response);
};

#endif // MODEL_H
