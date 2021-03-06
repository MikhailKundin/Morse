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
	QByteArray id = request.getCookie("id");
	QByteArray key = request.getCookie("key");
	
	// Если проверка не пройдена, удаление ключа из БД, чтобы пользователю
	// необходимо было заново пройти аутентификацию
	if (!database->isKeyExists(id, key))
	{
		database->updateKey(id, "");
		return false;
	}
	
	// Обновление ключа, если куки-таймер удалилась
	QByteArray update = request.getCookie("updateKey");
	if (update == "")
	{
		updateKey(request, response, id);
	}
	
	return true;
}

// Создание нового ключа
void Model::updateKey(HttpRequest &request, HttpResponse &response, QByteArray id)
{
	// Обновление куки-таймера
	response.setCookie(HttpCookie("updateKey", "Updated", 300)); // 5 минут
	
	// Генерация нового ключа
	HttpSession session = sessionStore->getSession(request, response);
	QByteArray key = session.getId();
	QByteArray salt = generateSalt();
	key = hashPassword(key, salt);
	
	// Запись ключа в БД
	database->updateKey(id, key);
	
	// Запись ключа в куку
	HttpCookie keyCookie("key", key, 31536000); // 365 дней
	keyCookie.setHttpOnly(true);
	response.setCookie(keyCookie);
}

// Хеширование пароля
QByteArray Model::hashPassword(QByteArray password, QByteArray salt)
{
	password += salt+"Gz7.kA02Gkl&QG>m";
	for (quint8 i = 0; i < 255; i++)
	{
		password = QCryptographicHash::hash(password, QCryptographicHash::Sha512);
	}
	return password;
}

// Генерация "соли"
QByteArray Model::generateSalt()
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
