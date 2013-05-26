TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += icondialog.h \
           iconlist.h \
           imagebutton.h \
           imagelabel.h \
           mainform.h \
           textedit.h \
           texteditlist.h
SOURCES += icondialog.cpp \
           iconlist.cpp \
           imagebutton.cpp \
           imagelabel.cpp \
           main.cpp \
           mainform.cpp \
           textedit.cpp \
           texteditlist.cpp
           
RESOURCES += resource.qrc

TRANSLATIONS = pole_ru.ts

win32 { 
  RC_FILE = icon.rc 
}