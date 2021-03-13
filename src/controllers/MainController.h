#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "AbstractController.h"

class MainView;
class MainModel;

class MainController : public AbstractController
{
public:
	MainController(QByteArray domain, qint32 port, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	MainModel* model;
	MainView* view;
	
	QByteArray m_domain = "";
	qint32 m_port = 0;
};

#endif // MAINCONTROLLER_H
