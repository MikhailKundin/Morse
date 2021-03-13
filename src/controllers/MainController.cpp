#include "MainController.h"

#include "../models/MainModel.h"
#include "../views/MainView.h"

MainController::MainController(QByteArray domain, qint32 port, QObject *parent) :
	AbstractController(parent)
{
	model = new MainModel(this);
	view = new MainView(this);
	
	m_domain = domain;
	m_port = port;
}

void MainController::service(HttpRequest &request, HttpResponse &response)
{
	if (request.getMethod() == "GET")
	{
		if (!model->isAuthorized(request, response))
		{
			response.redirect("http://"+m_domain+":"+QByteArray::number(m_port)+"/sign-in");
		}
		else
		{
			QString word = model->getWord(request, response);
			qint32 points = model->getPoints(request, response);
			view->service(request, response, word, QString::number(points));
		}
	}
	else
	{
		QString correctCode = "";
		QString message = "";
		if (model->checkCode(request, response, correctCode))
		{
			message = "Вы ответили правильно!";
			model->addPoints(request, response, 1);
		}
		else
		{
			message = "Вы ответили неправильно! Правильный ответ: "+correctCode;
		}
		
		QString word = model->getWord(request, response);
		qint32 points = model->getPoints(request, response);
		view->service(request, response, word, QString::number(points), message);
	}
}
