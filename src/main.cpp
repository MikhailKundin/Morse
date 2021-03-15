#include <QCoreApplication>
#include <QDir>

#include "MorseServer.h"
#include <QString>

using namespace stefanfrings;

QString searchConfigFile();

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	app.setApplicationName("MorseServer");
	
	qWarning("Application started");
	
	new MorseServer(searchConfigFile(), &app);
	
	return app.exec();
	
	qWarning("Application finished");
}

// Поиск файла с настрйками
QString searchConfigFile()
{
    QString binDir  = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();
    QString fileName(appName + ".ini");

    QStringList searchList;
	searchList.append(binDir);
	searchList.append(binDir+"/etc");
	searchList.append(binDir+"/../../../etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            fileName=QDir(file.fileName()).canonicalPath();
            qWarning("Using config file %s", qPrintable(fileName));
            return fileName;
        }
    }

    // Файл не найден
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found", qPrintable(dir), qPrintable(fileName));
    }
    qFatal("Cannot find config file %s", qPrintable(fileName));
	return "";
}
