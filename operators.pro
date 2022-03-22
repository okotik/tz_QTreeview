QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basereader.cpp \
    editoperator.cpp \
    main.cpp \
    tree.cpp \
    treemodel.cpp \
    treeviewdelegate.cpp

HEADERS += \
    basereader.h \
    editoperator.h \
    infostructures.h \
    tree.h \
    treemodel.h \
    treeviewdelegate.h

FORMS += \
    editoperator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
