#ifndef ACCESSMODEL_H
#define ACCESSMODEL_H

#include "Model.h"

class AccessModel : public Model
{
public:
	AccessModel(QObject* parent = nullptr);
	
	bool isRegistrationSuccessful(HttpRequest& request, HttpResponse& response);
	bool isAuthenticationSuccessful(HttpRequest& request, HttpResponse& response);
	void deauthorization(HttpRequest& request, HttpResponse& response);
};

#endif // ACCESSMODEL_H
