#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "AbstractController.h"

class MainView;
class MainModel;

class MainController : public AbstractController
{
public:
	MainController(QString domain, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	MainModel* model;
	MainView* view;
	
	QString m_domain = "";
};

#endif // MAINCONTROLLER_H
