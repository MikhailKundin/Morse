#include "AccessModel.h"

#include "../Database.h"
#include "httpsessionstore.h"

extern Database* database;
extern HttpSessionStore* sessionStore;

AccessModel::AccessModel(QObject *parent) :
	Model(parent)
{
	
}

// Добавление нового пользователя, если это возможно
bool AccessModel::isRegistrationSuccessful(HttpRequest &request, HttpResponse& response)
{
	Q_UNUSED(response)
	
	// Проверка на существующий логин
	QString login = request.getParameter("login");
	if (database->ifLoginExists(login))
	{
		return false;
	}
	
	QString password = request.getParameter("password");
	
	// Проверка размера пароля
	if (password.length() < 8)
	{
		return false;
	}
	
	// Проверка наличия заглавных, строчных символов и цифр в пароле
	bool lowercase = false;
	bool uppercase = false;
	bool number = false;
	for (qint16 i = 0; i < password.size(); i++)
	{
		QChar symbol = password.at(i);
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
	QString salt = generateSalt();
	password = hashPassword(password, salt);
	database->addUser(login, password, salt);
	return true;
}

// Аутентификация
bool AccessModel::isAuthenticationSuccessful(HttpRequest &request, HttpResponse &response)
{
	QString login = request.getParameter("login");
	QString password = request.getParameter("password");
	
	QString salt = "";
	QString hashedPassword = "";
	qint32 id = -1;
	
	// Получение из БД строки login
	// Если такой строки нет, то неправильный логин
	if (!database->getUserInfo(login, id, hashedPassword, salt))
	{
		return false;
	}
	
	// Если строка найдена, но значения по каким-то причинам не обновились, то ошибка
	if (salt == "" || hashedPassword == "" || id == -1)
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
	response.setCookie(HttpCookie("id", QByteArray::number(id), 31536000)); // 365 дней
	updateKey(request, response, id);
	
	return true;
}

// Удаление ключа из БД и куки
void AccessModel::deauthorization(HttpRequest &request, HttpResponse &response)
{
	qint32 id = request.getCookie("id").toInt();
	database->updateKey(id, "NULL");
	sessionStore->removeSession(sessionStore->getSession(request, response, false));
	response.setCookie(HttpCookie("key", "NULL", -1));
	response.setCookie(HttpCookie("id", "NULL", -1));
	response.setCookie(HttpCookie("updateKey", "NULL", -1));
	response.setCookie(HttpCookie("sessionid", "NULL", -1));
}
