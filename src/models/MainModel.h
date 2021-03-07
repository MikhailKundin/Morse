#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "Model.h"

class MainModel : public Model
{
public:
	MainModel(QObject* parent = nullptr);
	
	QString getWord();
	qint32 getPoints();
	bool isCodeCorrect(QString word);
};

#endif // MAINMODEL_H
