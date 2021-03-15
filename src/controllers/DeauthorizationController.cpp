#include "DeauthorizationController.h"

#include "../models/AccessModel.h"

DeauthorizationController::DeauthorizationController(QString domain, QObject *parent) :
	AbstractController(parent)
{
	model = new AccessModel(this);
	
	m_domain = domain;
}

void DeauthorizationController::service(HttpRequest &request, HttpResponse &response)
{
	model->deauthorization(request, response);
	response.redirect("http://"+m_domain.toUtf8()+"/sign-in");
}
