#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "AbstractView.h"

class MainView : public AbstractView
{
public:
	MainView(QObject* parent = nullptr);
	
	void service(HttpRequest& request, HttpResponse& response);
	void service(HttpRequest& request, HttpResponse& response, QString score, QString message);
	void service(HttpRequest& request, HttpResponse& response, QString score, QString message, QString error);
};

#endif // MAINVIEW_H
