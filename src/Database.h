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
	
	bool getUserInfo(QByteArray login, qint32& id, QByteArray& password, QByteArray& salt);
	
	void updateKey(qint32 id, QByteArray key);
	bool isKeyExists(qint32 id, QByteArray key);
	
	quint32 getWordCount();
	QString getWord(qint32 id);
	QString getCode(QString word);
	
	qint32 getPoints(qint32 id);
	void setPoints(qint32 id, qint32 points);
	
private:
	QSqlDatabase m_db;
};

#endif // DATABASE_H
