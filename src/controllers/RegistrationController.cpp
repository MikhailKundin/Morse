#include "RegistrationController.h"

#include "../models/AccessModel.h"
#include "../views/AccessView.h"

RegistrationController::RegistrationController(QByteArray domain, qint32 port, QObject *parent) :
	AbstractController(parent)
{
	model = new AccessModel(this);
	view = new AccessView(this);
	
	m_domain = domain;
	m_port = port;
}

void RegistrationController::service(HttpRequest &request, HttpResponse &response)
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
		if (model->isRegistrationSuccessful(request, response))
		{
			response.redirect("http://"+m_domain+":"+QByteArray::number(m_port)+"/sign-in");
		}
		else
		{
			view->service(request, response, "Логин уже существует");
		}
	}
}
