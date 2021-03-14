#include "Model.h"

#include <QCryptographicHash>
#include <QRandomGenerator>

#include "../Database.h"
#include "httpsessionstore.h"

extern Database* database;
extern HttpSessionStore* sessionStore;

Model::Model(QObject *parent)
	: QObject(parent)
{
	
}

// Авторизирован ли пользователь
bool Model::isAuthorized(HttpRequest &request, HttpResponse &response)
{
	qint32 id = request.getCookie("id").toInt();
	QString key = request.getCookie("key");
	
	if (key == "NULL" || key == "")
	{	
		return false;
	}
	
	// Если проверка не пройдена, удаление ключа из БД, чтобы пользователю
	// необходимо было заново пройти аутентификацию
	if (!database->isKeyExists(id, key))
	{
		database->updateKey(id, "NULL");
		return false;
	}
	
	// Обновление ключа, если куки-таймер удалилась
	QString update = request.getCookie("updateKey");
	if (update == "")
	{
		updateKey(request, response, id);
	}
	
	return true;
}

// Создание нового ключа
void Model::updateKey(HttpRequest &request, HttpResponse &response, qint32 id)
{
	// Обновление куки-таймера
	response.setCookie(HttpCookie("updateKey", "Updated", 300)); // 5 минут
	
	// Генерация нового ключа
	HttpSession session = sessionStore->getSession(request, response);
	QString key = session.getId();
	QString salt = generateSalt();
	key = hashPassword(key, salt);
	
	// Запись ключа в БД
	database->updateKey(id, key);
	
	// Запись ключа в куку
	HttpCookie keyCookie("key", key.toUtf8(), 31536000); // 365 дней
	keyCookie.setHttpOnly(true);
	response.setCookie(keyCookie);
}

// Хеширование пароля
QString Model::hashPassword(QString password, QString salt)
{
	password += salt+"Gz7.kA02Gkl&QG>m";
	for (quint8 i = 0; i < 255; i++)
	{
		password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha512).toHex();
	}
	return password;
}

// Генерация "соли"
QString Model::generateSalt()
{
	QString salt;
	QString saltSymbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
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
