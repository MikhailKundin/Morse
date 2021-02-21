#ifndef GLOBAL_H
#define GLOBAL_H

#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "templatecache.h"
#include "filelogger.h"

using namespace stefanfrings;

extern HttpSessionStore* sessionStore;
extern StaticFileController* staticFileController;
extern TemplateCache* templateCache;
extern FileLogger* fileLogger;

#endif // GLOBAL_H
