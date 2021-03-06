#include "AccessModel.h"

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
	
	QByteArray salt = "";
	QByteArray hashedPassword = "";
	QByteArray id = "";
	
	// Получение из БД строки login
	// Если такой строки нет, то неправильный логин
	if (!database->getUserInfo(login, id, password, salt))
	{
		return false;
	}
	
	// Если строка найдена, но значения по каким-то причинам не обновились, то ошибка
	if (salt == "" || hashedPassword == "" || id == "")
	{
		return false;
	}
	
	// Хеширование введенного пароля и сравнение его с паролем из БД.
	// Если пароли не совпадают, то ошибка
	password = hashPassword(password, salt);
	if (password != hashedPassword)
	{
		return false;
	}
	
	// Создание ключа аутентификации и кук
	response.setCookie(HttpCookie("id", id, 31536000)); // 365 дней
	updateKey(request, response, id);
	
	return true;
}
