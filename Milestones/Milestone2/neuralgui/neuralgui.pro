QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
    # https://stackoverflow.com/questions/23134937/qt-creator-on-mac-and-boost-libraries
    _BOOST_PATH = /usr/local/Cellar/boost/1.71.0/
    INCLUDEPATH += "$${_BOOST_PATH}/include/"
    LIBS += -L$${_BOOST_PATH}/lib
    ## Use only one of these:
    LIBS += -lboost_system -lboost_filesystem # using dynamic lib (not sure if you need that "-mt" at the end or not)
    #LIBS += $${_BOOST_PATH}/lib/libboost_chrono-mt.a # using static lib
}

# add your INCLUDEPATH (see above for mac) for your system
# INCLUDEPATH +=
LIBS += -lboost_system -lboost_filesystem # using dynamic lib (not sure if you need that "-mt" at the end or not)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
#    ../code/src/fcnn.cpp \
    ../code/src/layer.cpp \
    ../code/src/multi_layer_perceptron.cpp \
#    ../code/src/controller.cpp \

HEADERS += \
    mainwindow.h \
    ../code/include/layer.hpp \
    ../code/include/multi_layer_perceptron.hpp \
#    ../code/include/controller.h \

FORMS += \
    mainwindow.ui

include(qcustomplot/qcustomplot.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
