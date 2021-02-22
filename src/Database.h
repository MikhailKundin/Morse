#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSettings>
#include <QSqlDatabase>

class Database : public QObject
{
public:
	Database(QSettings* databaseSettings, QObject* parent = nullptr);
	
	bool ifLoginExists(QByteArray login);
	void addUser(QByteArray login, QByteArray password, QByteArray salt);
	
	QByteArray getSalt(QByteArray login);
	bool isUserExists(QByteArray login, QByteArray password);
	
	void addKey(QByteArray login, QByteArray key);
	bool isKeyCorrect(QByteArray login, QByteArray key);
	
	qint32 getWordCount();
	QString getWord(qint32 id);
	QString getCode(QString word);
	
	qint32 getPoints(QString login);
	void setPoints(QString login);
	
private:
	QSqlDatabase m_db;
};

#endif // DATABASE_H
