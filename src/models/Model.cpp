#include "Model.h"

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
		updateKey(request, response);
	}
	
	return true;
}

// Создание нового ключа
void Model::updateKey(HttpRequest &request, HttpResponse &response)
{
	// Обновление куки-таймера
	response.setCookie(HttpCookie("updateKey", "Updated", 300)); // 5 минут
	
	// Генерация нового ключа
	HttpSession session = sessionStore->getSession(request, response);
	QByteArray key = session.getId();
	sessionStore->removeSession(session);
	response.setCookie(HttpCookie("sessionid", "", 0));
	
	// Запись ключа в БД
	QByteArray id = request.getCookie("id");
	database->updateKey(id, key);
	
	// Запись ключа в куку
	HttpCookie keyCookie("key", key, 31536000); // 365 дней
	keyCookie.setHttpOnly(true);
	response.setCookie(keyCookie);
}
