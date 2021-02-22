QT -= gui
QT += core network sql

TARGET = MorseServer
TEMPLATE = app

CONFIG += c++17 console
CONFIG -= app_bundle debug_and_release debug_and_release_target

CONFIG(debug, debug|release){
win32:DESTDIR = build/Windows/debug
win32:OBJECTS_DIR = build/Windows/temp/debug/obj
win32:MOC_DIR = build/Windows/temp/debug/moc
win32:RCC_DIR = build/Windows/temp/debug/rcc
win32:UI_DIR = build/Windows/temp/debug/ui

unix:DESTDIR = build/Unix/debug
unix:OBJECTS_DIR = build/Unix/temp/debug/obj
unix:MOC_DIR = build/Unix/temp/debug/moc
unix:RCC_DIR = build/Unix/temp/debug/rcc
unix:UI_DIR = build/Unix/temp/debug/ui
}

CONFIG(release, debug|release){
win32:DESTDIR = build/Windows/Tetris
win32:OBJECTS_DIR = build/Windows/temp/release/obj
win32:MOC_DIR = build/Windows/temp/release/moc
win32:RCC_DIR = build/Windows/temp/release/rcc
win32:UI_DIR = build/Windows/temp/release/ui

unix:DESTDIR = build/Unix/Tetris
unix:OBJECTS_DIR = build/Unix/temp/release/obj
unix:MOC_DIR = build/Unix/temp/release/moc
unix:RCC_DIR = build/Unix/temp/release/rcc
unix:UI_DIR = build/Unix/temp/release/ui
}

include(QtWebApp/httpserver/httpserver.pri)
include(QtWebApp/logging/logging.pri)
include(QtWebApp/templateengine/templateengine.pri)

SOURCES += \
        src/Database.cpp \
        src/MorseServer.cpp \
        src/controllers/AbstractController.cpp \
        src/controllers/AuthenticationController.cpp \
        src/controllers/MainController.cpp \
        src/controllers/RegistrationController.cpp \
        src/main.cpp \
        src/models/AccessModel.cpp \
        src/models/Model.cpp

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
	src/Database.h \
	src/MorseServer.h \
	src/controllers/AbstractController.h \
	src/controllers/AuthenticationController.h \
	src/controllers/MainController.h \
	src/controllers/RegistrationController.h \
	src/models/AccessModel.h \
	src/models/Model.h
