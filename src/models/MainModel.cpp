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

// Получение слоучайного слова из БД
QString MainModel::getWord(HttpRequest &request, HttpResponse &response)
{
	// Получение слова из БД
	quint32 wordCount = database->getWordCount();
	qint32 wordId = static_cast<qint32>(QRandomGenerator::global()->generate() % wordCount + 1);
	QString word = database->getWord(wordId);
	
	// Запись слова в сессию
	HttpSession session = sessionStore->getSession(request, response);
	session.set("word", word);
	
	return word;
}

// Получение количества очков пользователя
qint32 MainModel::getPoints(HttpRequest &request, HttpResponse& response)
{
	Q_UNUSED(response)
	
	qint32 id = request.getCookie("id").toInt();
	qint32 points = database->getPoints(id);
	return points;
}

// Проверка правильности кода
bool MainModel::checkCode(HttpRequest &request, HttpResponse &response, QString &correctCode)
{
	// Получение слова из сессии
	HttpSession session = sessionStore->getSession(request, response);
	QString word = session.get("word").toString();
	
	// Получение кода из куки
	QString code = request.getParameter("code");
	
	// Получени кода из БД
	correctCode = database->getCode(word);
	
	// Сравнение кодов
	if (code == correctCode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Добавление очков пользователю
void MainModel::addPoints(HttpRequest &request, HttpResponse& response, qint32 num)
{
	Q_UNUSED(response)
	
	qint32 id = request.getCookie("id").toInt();
	qint32 points = database->getPoints(id);
	points += num;
	database->setPoints(id, points);
}
