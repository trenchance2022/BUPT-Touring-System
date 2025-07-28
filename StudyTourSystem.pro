QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    destinationrecommend.cpp \
    diarycreate.cpp \
    diarymanagement.cpp \
    diaryview.cpp \
    editmultipoint.cpp \
    functionselectpage.cpp \
    main.cpp \
    login.cpp \
    cJSON.c \
    login_page.cpp \
    huffman.cpp \
    kmp.cpp \
    myGraph.cpp \
    mylabel.cpp \
    mymap.cpp \
    route_plan.cpp

HEADERS += \
    destinationrecommend.h \
    diarycreate.h \
    diarymanagement.h \
    diaryview.h \
    editmultipoint.h \
    functionselectpage.h \
    json.hpp \
    login.h \
    cJSON.h \
    login_page.h \
    huffman.h \
    kmp.h \
    myGraph.h \
    mylabel.h \
    mymap.h \
    route_plan.h

FORMS += \
    destinationrecommend.ui \
    diarycreate.ui \
    diarymanagement.ui \
    diaryview.ui \
    editmultipoint.ui \
    functionselectpage.ui \
    login.ui \
    mymap.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bupt_map.json \
    diaries.json \
    data_map.json

RESOURCES +=
