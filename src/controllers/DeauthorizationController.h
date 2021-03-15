#ifndef DEAUTHORIZATIONCONTROLLER_H
#define DEAUTHORIZATIONCONTROLLER_H

#include "AbstractController.h"

class AccessModel;

class DeauthorizationController : public AbstractController
{
public:
	DeauthorizationController(QString domain, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	AccessModel* model;
	
	QString m_domain = "";
};

#endif // DEAUTHORIZATIONCONTROLLER_H
