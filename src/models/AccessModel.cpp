#include "AccessModel.h"

#include <QCryptographicHash>
#include <QRandomGenerator>

#include "../Database.h"

extern Database* database;
extern HttpSessionStore* sessionStore;

AccessModel::AccessModel(QObject *parent)
	: Model(parent)
{
	
}

// Добавление нового пользователя, если это возможно
bool AccessModel::isRegistrationSuccessful(HttpRequest &request)
{
	// Проверка на существующий логин
	QByteArray login = request.getParameter("login");
	if (database->ifLoginExists(login))
	{
		return false;
	}
	
	QByteArray password = request.getParameter("password");
	
	// Проверка размера пароля
	if (password.length() < 8)
	{
		return false;
	}
	
	// Проверка наличия заглавных, строчных символов и цифр в пароле
	bool lowercase = false;
	bool uppercase = false;
	bool number = false;
	QString passUtf8 = QString::fromUtf8(password);
	for (qint16 i = 0; i < passUtf8.size(); i++)
	{
		QChar symbol = passUtf8.at(i);
		if (symbol.isUpper())
		{
			uppercase = true;
		}
		else if (symbol.isLower())
		{
			lowercase = true;
		}
		else if (symbol.isNumber())
		{
			number = true;
		}
		
		if (lowercase && uppercase && number)
		{
			break;
		}
	}
	if (!(lowercase && uppercase && number))
	{
		return false;
	}
	
	// Добавление нового пользователя
	QByteArray salt = generateSalt();
	password = hashPassword(password, salt);
	database->addUser(login, password, salt);
	return true;
}

// Аутентификация
bool AccessModel::isAuthenticationSuccessful(HttpRequest &request, HttpResponse &response)
{
	QByteArray login = request.getParameter("login");
	QByteArray password = request.getParameter("password");
	QByteArray salt = database->getSalt(login);
	password = hashPassword(password, salt);
	//if ()
	return false;
}

// Хеширование пароля
QByteArray AccessModel::hashPassword(QByteArray password, QByteArray salt)
{
	password += salt+"Gz7.kA02Gkl&QG>m";
	for (quint8 i = 0; i < 255; i++)
	{
		password = QCryptographicHash::hash(password, QCryptographicHash::Sha512);
	}
	return password;
}

// Генерация "соли"
QByteArray AccessModel::generateSalt()
{
	QByteArray salt;
	QByteArray saltSymbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							 "abcdefghijklmnopqrstuvwxyz"
							 "0123456789"
							 "!@#$%^&*()_+№;:?-+{}[]<>,.";
	quint8 range = static_cast<quint8>(saltSymbols.length());
	qint8 length = QRandomGenerator::global()->generate() % 7 + 10;
	for (qint8 i = 0; i < length; i++)
	{
		salt += saltSymbols.at(static_cast<char>(QRandomGenerator::global()->generate() % range));
	}
	return salt;
}
