#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "Model.h"

class MainModel : public Model
{
public:
	MainModel(QObject* parent = nullptr);
	
	QString getWord(HttpRequest& request, HttpResponse& response);
	qint32 getPoints(HttpRequest& request, HttpResponse& response);
	bool checkCode(HttpRequest& request, HttpResponse& response, QString& correctCode);
	void addPoints(HttpRequest& request, HttpResponse& response, qint32 num);
};

#endif // MAINMODEL_H
