#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include "AbstractController.h"

class AccessView;
class AccessModel;

class RegistrationController : public AbstractController
{
public:
	RegistrationController(QByteArray domain, qint32 port, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	AccessModel* model;
	AccessView* view;

	QByteArray m_domain = "";
	qint32 m_port = 0;
};

#endif // REGISTRATIONCONTROLLER_H
