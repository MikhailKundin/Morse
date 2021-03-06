#ifndef MODEL_H
#define MODEL_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class Model : public QObject
{
public:
	Model(QObject* parent = nullptr);
	virtual bool isAuthorized(HttpRequest& request, HttpResponse& response);
	virtual void updateKey(HttpRequest& request, HttpResponse& response, QByteArray id);
	
protected:
	QByteArray hashPassword(QByteArray password, QByteArray salt);
	QByteArray generateSalt();
};

#endif // MODEL_H
