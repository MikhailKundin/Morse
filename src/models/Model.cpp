#include "Model.h"

#include "../Database.h"

extern Database* database;

Model::Model(QObject *parent)
	: QObject(parent)
{
	
}

// Авторизирован ли пользователь
bool Model::isAuthorized(HttpRequest &request)
{
	QByteArray login = request.getCookie("login");
	QByteArray key = request.getCookie("key");
	return database->isKeyCorrect(login, key);
}
