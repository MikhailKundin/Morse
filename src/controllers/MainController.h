#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "AbstractController.h"

class MainController : public AbstractController
{
public:
	MainController(QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
};

#endif // MAINCONTROLLER_H
