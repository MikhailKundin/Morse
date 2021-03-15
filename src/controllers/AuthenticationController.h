#ifndef AUTHENTICATIONCONTROLLER_H
#define AUTHENTICATIONCONTROLLER_H

#include "AbstractController.h"

class AccessView;
class AccessModel;

class AuthenticationController : public AbstractController
{
public:
	AuthenticationController(QString domain, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	AccessModel* model;
	AccessView* view;
	
	QString m_domain = "";
};

#endif // AUTHENTICATIONCONTROLLER_H
