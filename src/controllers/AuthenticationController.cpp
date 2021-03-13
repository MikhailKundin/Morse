#include "AuthenticationController.h"

#include "../models/AccessModel.h"
#include "../views/AccessView.h"

AuthenticationController::AuthenticationController(QByteArray domain, qint32 port, QObject *parent) :
	AbstractController(parent)
{
	model = new AccessModel(this);
	view = new AccessView(this);
	
	m_domain = domain;
	m_port = port;
}

void AuthenticationController::service(HttpRequest &request, HttpResponse &response)
{
	if (request.getMethod() == "GET")
	{
		if (model->isAuthorized(request, response))
		{
			response.redirect("http://"+m_domain+":"+QByteArray::number(m_port)+"/main");
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
			response.redirect("http://"+m_domain+":"+QByteArray::number(m_port)+"/main");
		}
		else
		{
			view->service(request, response, "Неправильный логин или пароль");
		}
	}
}
