#include "AccessView.h"

#include "templatecache.h"
#include "template.h"

extern TemplateCache* templateCache;

AccessView::AccessView(QObject *parent) :
	AbstractView(parent)
{
	
}

// Вывод страницы без сообщений от сервера
void AccessView::service(HttpRequest &request, HttpResponse &response)
{
	service(request, response, "");
}

// Вывод страницы с сообщениями от сервера
void AccessView::service(HttpRequest &request, HttpResponse &response, QString message)
{
	if (request.getPath() == "/sign-in") // Страница авторизации
	{
		Template temp = templateCache->getTemplate("auth");
		temp.setVariable("message", message); // Неправильный логин или пароль
		response.write(temp.toUtf8(), true);
	}
	else if (request.getPath() == "/sign-up") // Стрраница регистрации
	{
		Template temp = templateCache->getTemplate("reg");
		temp.setVariable("message", message); // Логин уже существует
		response.write(temp.toUtf8(), true);
	}
	else // Ошибка
	{
		response.setStatus(404, "Not found");
		response.write(qPrintable(QString::fromUtf8("404: Страница не найдена")));
	}
}
