#include "MainView.h"

#include "templatecache.h"
#include "template.h"

extern TemplateCache* templateCache;

MainView::MainView(QObject *parent) :
	AbstractView(parent)
{
	
}

// Вывод страницы без сообщений от сервера
void MainView::service(HttpRequest &request, HttpResponse &response)
{
	service(request, response, "", "", "");
}

// Вывод страницы с загаданным словом и количеством очков, но без предыдущего результата
void MainView::service(HttpRequest &request, HttpResponse &response, QString score, QString message)
{
	service(request, response, score, message, "");
}

// Вывод страницы с сообщениями от сервера
void MainView::service(HttpRequest &request, HttpResponse &response, QString score, QString message, QString error)
{
	if (request.getPath() == "/main") // Главная траница
	{
		Template temp = templateCache->getTemplate("main");
		temp.setVariable("Score", score); // Количество очков
		temp.setVariable("Message", message); // Слово
		temp.setVariable("err", error); // Предыдущий результат
		response.write(temp.toUtf8(), true);
	}
	else // Ошибка
	{
		response.setStatus(404, "Not found");
		response.write(qPrintable(QString::fromUtf8("404: Страница не найдена")));
	}
}

