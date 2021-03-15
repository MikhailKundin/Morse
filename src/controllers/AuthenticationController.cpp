#include "AuthenticationController.h"

#include "../models/AccessModel.h"
#include "../views/AccessView.h"

AuthenticationController::AuthenticationController(QString domain, QObject *parent) :
	AbstractController(parent)
{
	model = new AccessModel(this);
	view = new AccessView(this);
	
	m_domain = domain;
}

void AuthenticationController::service(HttpRequest &request, HttpResponse &response)
{
	if (request.getMethod() == "GET")
	{
		if (model->isAuthorized(request, response))
		{
			response.redirect("http://"+m_domain.toUtf8()+"/main");
		}
		else
		{
			view->service(request, response);
		}
	}
	else
	{
		if (model->isAuthenticationSuccessful(request, response))
		{
			response.redirect("http://"+m_domain.toUtf8()+"/main");
		}
		else
		{
			view->service(request, response, "Неправильный логин или пароль");
		}
	}
}
