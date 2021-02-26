#include "Database.h"

#include <QSqlQuery>
#include <QSqlError>

Database::Database(QSettings *databaseSettings, QObject *parent)
	: QObject(parent)
{
	m_db = QSqlDatabase::addDatabase(databaseSettings->value("type").toString());
	m_db.setDatabaseName(databaseSettings->value("dbName").toString());
	m_db.setHostName(databaseSettings->value("hostName").toString());
	m_db.setUserName(databaseSettings->value("userName").toString());
	m_db.setPassword(databaseSettings->value("password").toString());
	m_db.setPort(databaseSettings->value("port").toInt());
	qDebug("ping");
	if (m_db.open())
	{
		qInfo("Connected to database");
//		QSqlQuery query(m_db);
//		query.prepare("Select name from RecordTable "
//					  "where id = 1");
//		query.exec();
//		qDebug(qPrintable(query.value(0).toString()));
	}
	else
	{
		qDebug(qPrintable(m_db.lastError().databaseText()));
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

QByteArray Database::getSalt(QByteArray login)
{
	return "";
}

// Поиск связки логин-пароль в БД
bool Database::isUserExists(QByteArray login, QByteArray password)
{
	return false;
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
void Database::setPoints(QByteArray id)
{
	
}
