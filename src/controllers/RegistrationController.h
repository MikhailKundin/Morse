#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include "AbstractController.h"

class RegistrationController : public AbstractController
{
public:
	RegistrationController(QObject* parent = nullptr);
	virtual void requestHandler(HttpRequest& request, HttpResponse& response) override;
};

#endif // REGISTRATIONCONTROLLER_H
