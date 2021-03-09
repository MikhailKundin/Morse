#ifndef ACCESSVIEW_H
#define ACCESSVIEW_H

#include "AbstractView.h"

class AccessView : public AbstractView
{
public:
	AccessView(QObject* parent = nullptr);
	
	void service(HttpRequest& request, HttpResponse& response) override;
	void service(HttpRequest& request, HttpResponse& response, QString message);
};

#endif // ACCESSVIEW_H
