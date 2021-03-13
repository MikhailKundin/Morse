#ifndef DEAUTHORIZATIONCONTROLLER_H
#define DEAUTHORIZATIONCONTROLLER_H

#include "AbstractController.h"

class AccessModel;

class DeauthorizationController : public AbstractController
{
public:
	DeauthorizationController(QByteArray domain, qint32 port, QObject* parent = nullptr);
	virtual void service(HttpRequest& request, HttpResponse& response) override;
	
private:
	AccessModel* model;
	
	QByteArray m_domain = "";
	qint32 m_port = 0;
};

#endif // DEAUTHORIZATIONCONTROLLER_H
