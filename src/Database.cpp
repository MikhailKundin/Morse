#include "Database.h"

#include <QSqlQuery>

Database::Database(QSettings *databaseSettings, QObject *parent)
	: QObject(parent)
{
	qInfo("Connecting to database...");
	m_db = QSqlDatabase::addDatabase(databaseSettings->value("type").toString());
	m_db.setDatabaseName(databaseSettings->value("dbName").toString());
	m_db.setHostName(databaseSettings->value("hostName").toString());
	m_db.setPort(databaseSettings->value("port").toInt());
	m_db.setUserName(databaseSettings->value("userName").toString());
	m_db.setPassword(databaseSettings->value("password").toString());
	if (m_db.open())
	{
		qInfo("Connected to database");
	}
	else
	{
		qFatal("Unable to connect to database");
	}
}

// Проверка наличия логина в БД
bool Database::ifLoginExists(QByteArray login)
{
	return false;
}

// Добавление логина и пароля в БД
void Database::addUser(QByteArray login, QByteArray password, QByteArray salt)
{
	
}

//QByteArray Database::getSalt(QByteArray login)
//{
//	return "";
//}

// Поиск связки логин-пароль в БД
//bool Database::isUserExists(QByteArray login, QByteArray password)
//{
//	return false;
//}

bool Database::getUserInfo(QByteArray login, QByteArray &id, QByteArray &password, QByteArray &salt)
{
	
}

// Добавление ключа конкретному логину
void Database::updateKey(QByteArray id, QByteArray key)
{
	
}

// Поиск связки логин-ключ
bool Database::isKeyExists(QByteArray id, QByteArray key)
{
	return false;
}

// Получение количества слов в БД
qint32 Database::getWordCount()
{
	return 0;
}

// Прлучение слова с заданным ID из БД
QString Database::getWord(qint32 id)
{
	return "";
}

// Получение кода конкретного слова
QString Database::getCode(QString word)
{
	return "";
}

// Получение очков логина
qint32 Database::getPoints(QByteArray id)
{
	return 0;
}

// Запись очков логину
void Database::setPoints(QByteArray id, qint32 points)
{
	
}
