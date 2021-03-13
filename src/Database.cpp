#include "Database.h"

#include <QSqlQuery>
#include <QSqlError>

Database::Database(QSettings *databaseSettings, QObject *parent)
	: QObject(parent)
{
	// Соединение с БД
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
	QSqlQuery query(m_db);
	
	// Поиск строки, содержащей login
	query.prepare("select a.login "
				  "from morse.authentication a "
				  "where a.login = :login");
	query.bindValue(":login", login);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Login search failed");
	}
	
	if (query.first())
	{
		qDebug("%s exists", qPrintable(login));
		return true;
	}
	else
	{
		qDebug("%s does not exists", qPrintable(login));
		return false;
	}
}

// Добавление логина и пароля в БД
void Database::addUser(QByteArray login, QByteArray password, QByteArray salt)
{
	QSqlQuery query(m_db);
	// Добавление login, password, salt в базу данных
	query.prepare("insert into morse.authentication (login, \"password\", salt) "
				  "values (:login, :password, :salt)");
	query.bindValue(":login", login);
	query.bindValue(":password", password);
	query.bindValue(":salt", salt);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Failed to add user to database");
	}
	
	// Добавление новой строки в таблицу авторизации
	query.prepare("insert into morse.\"authorization\" (id_au, \"key\") "
				  "select a.id, :key from morze.authentication "
				  "where a.login = :login");
	query.bindValue(":key", "NULL");
	query.bindValue(":login", login);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error adding row to authorization table");
	}
	
	// Добавление новой строки в таблицу результатов
	query.prepare("insert into morze.records (id_au, \"result\") "
				  "select a.id, :result "
				  "from morze.authentication "
				  "where a.login = :login");
	query.bindValue(":result", 0);
	query.bindValue(":login", login);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while adding row to records table");
	}
}

// Получение идентификатора, пароля и соли пользователя
bool Database::getUserInfo(QByteArray login, qint32 &id, QByteArray &password, QByteArray &salt)
{
	QSqlQuery query(m_db);
	
	// Получение значений id, password и salt из строки, которая содержит login
	query.prepare("select a.id, a.password, a.salt "
				  "from morse.authentication a "
				  "where a.login = :login");
	query.bindValue(":login", login);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error retrieving user information from the DB");
	}
	
	if (!query.first())
	{
		return false;
	}
	
	id = query.value(0).toInt();
	password = query.value(1).toByteArray();
	salt = query.value(2).toByteArray();
	
	return true;
}

// Добавление ключа конкретному пользователю
void Database::updateKey(qint32 id, QByteArray key)
{
	QSqlQuery query(m_db);
	
	// Обновления значения key в строке, которая содержит id
	query.prepare("update morze.\"authorization\" az "
				  "set \"key\" = :key "
				  "where id_au = :id");
	query.bindValue("id", id);
	query.bindValue("key", key);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Key update error");
	}
}

// Поиск связки пользоваетль-ключ
bool Database::isKeyExists(qint32 id, QByteArray key)
{
	QSqlQuery query(m_db);
	
	// Поиск строки, которая содержит id и key
	query.prepare("select * "
				  "from morse.authorization az "
				  "where az.id_au=:id and az.key=:key");
	query.bindValue(":id", id);
	query.bindValue(":key", key);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while searching for an authorization key in the DB");
	}
	
	if (query.first())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Получение количества слов в БД
quint32 Database::getWordCount()
{
	QSqlQuery query(m_db);
	
	// Получения количества строк в таблице dictionary
	query.prepare("select count(*) "
				  "from morse.dictionary d");
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while getting the number of lines in the dictionary");
	}
	
	if (!query.first())
	{
		qFatal("Error while reading the number of lines in the dictionary ");
		return 0;
	}
	else
	{
		quint32 count = query.value(0).toUInt();
		qDebug("The dictionary has %s lines", qPrintable(QString::number(count)));
		return count;
	}
}

// Прлучение слова с заданным ID из БД
QString Database::getWord(qint32 id)
{
	QSqlQuery query(m_db);
	
	// Получение слова из строки, которая содержит значение id
	query.prepare("select d.word "
				  "from morse.dictionary d "
				  "where d.id = :id");
	query.bindValue(":id", id);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while searching for a word with id %s in the dictionary", qPrintable(QString::number(id)));
	}
	
	if (!query.first())
	{
		qFatal("Word with id %s does not exist", qPrintable(QString::number(id)));
		return "";
	}
	else
	{
		QString word = query.value(0).toString();
		qDebug("Found the word \"%s\" by id %s", qPrintable(word), qPrintable(QString::number(id)));
		return word;
	}
}

// Получение кода конкретного слова
QString Database::getCode(QString word)
{
	QSqlQuery query(m_db);
	
	// Получение кода из строки, которая содержит word
	query.prepare("select d.code "
				  "from morse.dictionary d "
				  "where d.word = :word");
	query.bindValue(":word", word);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while searching for a code of the word \"%s\" in the dictionary", qPrintable(word));
	}
	
	if (!query.first())
	{
		qFatal("Word %s does not exist", qPrintable(word));
		return "";
	}
	else
	{
		QString code = query.value(0).toString();
		qDebug("Found code \"%s\" of the word \"%s\"", qPrintable(code), qPrintable(word));
		return code;
	}
}

// Получение очков пользователя
qint32 Database::getPoints(qint32 id)
{
	QSqlQuery query(m_db);
	
	// Поиск количества очков в строке, которая содержит id
	query.prepare("select r.\"result\" "
				  "from morse.records r "
				  "where r.id_au = :id");
	query.bindValue(":id", id);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while searching for the number of points for user ID %s in the results table", 
			   qPrintable(QString::number(id)));
	}
	
	if (!query.first())
	{
		qFatal("User line with ID %s was not found in the results table", qPrintable(QString::number(id)));
		return 0;
	}
	else
	{
		qint32 points = query.value(0).toInt();
		qDebug("User %s has %s points ", qPrintable(QString::number(id)), qPrintable(QString::number(points)));
		return points;
	}
}

// Запись очков логину
void Database::setPoints(qint32 id, qint32 points)
{
	QSqlQuery query(m_db);
	
	// Обновление значения points в строке, которая содержит id
	query.prepare("update morze.records "
				  "set \"result\" = :points "
				  "where id_au = :id");
	query.bindValue(":id", id);
	query.bindValue(":points", points);
	if (!query.exec())
	{
		qWarning(qPrintable(query.lastError().text()));
		qFatal("Error while updating points for the user %s", qPrintable(QString::number(id)));
	}
}
