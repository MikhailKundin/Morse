#ifndef AUTHENTICATIONCONTROLLER_H
#define AUTHENTICATIONCONTROLLER_H

#include "AbstractController.h"

class AuthenticationController : public AbstractController
{
public:
	AuthenticationController(QObject* parent = nullptr);
	virtual void requestHandler(HttpRequest& request, HttpResponse& response) override;
};

#endif // AUTHENTICATIONCONTROLLER_H