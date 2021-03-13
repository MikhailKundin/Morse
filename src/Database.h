#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSettings>
#include <QSqlDatabase>

class Database : public QObject
{
public:
	Database(QSettings* databaseSettings, QObject* parent = nullptr);
	
	bool ifLoginExists(QString login);
	void addUser(QString login, QString password, QString salt);
	
	bool getUserInfo(QString login, qint32& id, QString& password, QString& salt);
	
	void updateKey(qint32 id, QString key);
	bool isKeyExists(qint32 id, QString key);
	
	quint32 getWordCount();
	QString getWord(qint32 id);
	QString getCode(QString word);
	
	qint32 getPoints(qint32 id);
	void setPoints(qint32 id, qint32 points);
	
private:
	QSqlDatabase m_db;
};

#endif // DATABASE_H
