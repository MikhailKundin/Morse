#ifndef MODEL_H
#define MODEL_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class Model : public QObject
{
public:
	Model(QObject* parent = nullptr);
	virtual ~Model() = default;
	virtual bool isAuthorized(HttpRequest& request, HttpResponse& response);
	
protected:
	virtual void updateKey(HttpRequest& request, HttpResponse& response, qint32 id);
	virtual QByteArray hashPassword(QByteArray password, QByteArray salt);
	virtual QByteArray generateSalt();
};

#endif // MODEL_H
