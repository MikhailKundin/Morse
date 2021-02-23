#ifndef ACCESSMODEL_H
#define ACCESSMODEL_H

#include "Model.h"

class AccessModel : public Model
{
public:
	AccessModel(QObject* parent = nullptr);
	
	bool isRegistrationSuccessful(HttpRequest& request);
	bool isAuthenticationSuccessful(HttpRequest& request, HttpResponse& response);
	
private:
	QByteArray hashPassword(QByteArray password, QByteArray salt);
	QByteArray generateSalt();
};

#endif // ACCESSMODEL_H