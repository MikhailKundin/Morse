#include "MainModel.h"

#include <QRandomGenerator>

#include "../Database.h"
#include "httpsessionstore.h"

extern Database* database;
extern HttpSessionStore* sessionStore;

MainModel::MainModel(QObject *parent) :
	Model(parent)
{
	
}

QString MainModel::getWord()
{
	// Получение слова из БД
	quint32 wordCount = database->getWordCount();
	qint32 wordId = static_cast<qint32>(QRandomGenerator::global()->generate() % wordCount);
	QString word = database->getWord(wordId);
	
	
}
