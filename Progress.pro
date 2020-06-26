TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    indice.cpp \
        main.cpp \
    user.cpp \
    menu.cpp \
    character.cpp \
    file_administrator.cpp \
    location.cpp

HEADERS += \
    indice.h \
    user.h \
    menu.h \
    lista_doble_ligada.h \
    character.h \
    file_administrator.h \
    grafo.h \
    location.h
