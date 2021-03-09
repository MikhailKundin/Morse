#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "Model.h"

class MainModel : public Model
{
public:
	MainModel(QObject* parent = nullptr);
	
	QString getWord(HttpRequest& request, HttpResponse& response);
	qint32 getPoints(HttpRequest& request);
	bool checkCode(HttpRequest& request, HttpResponse& response, QString& correctCode);
	void addPoints(HttpRequest& request, qint32 num);
};

#endif // MAINMODEL_H
