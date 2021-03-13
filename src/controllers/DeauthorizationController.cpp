#include "DeauthorizationController.h"

#include "../models/AccessModel.h"

DeauthorizationController::DeauthorizationController(QByteArray domain, qint32 port, QObject *parent) :
	AbstractController(parent)
{
	model = new AccessModel(this);
	
	m_domain = domain;
	m_port = port;
}

void DeauthorizationController::service(HttpRequest &request, HttpResponse &response)
{
	model->deauthorization(request, response);
	response.redirect("http://"+m_domain+":"+QByteArray::number(m_port)+"/sign-in");
}
