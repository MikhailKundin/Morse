#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include "AbstractController.h"

class AccessView;
class AccessModel;

class RegistrationController : public AbstractController
{
public:
	RegistrationController(QString domain, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	AccessModel* model;
	AccessView* view;

	QString m_domain = "";
};

#endif // REGISTRATIONCONTROLLER_H
