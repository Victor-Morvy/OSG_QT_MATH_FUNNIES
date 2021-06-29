QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    OsgQtWidget.h \
    PaintBezier.h \
    draw.h \
    mainwindow.h

FORMS += \
    mainwindow.ui




INCLUDEPATH += /usr/local/include
INCLUDEPATH += /home/victor/tests/MathFunies

unix|win32: LIBS += -L"/usr/local/lib" -losg -losgGA -losgAnimation -losgDB -losgViewer -losgWidget -losgUtil -losgSim -losgUI \
                    -losgManipulator  -losgFX -losgPresentation

LIBS += -L"/usr/local/lib64" -losgQt5
LIBS += -L"/home/victor/build-MathFunies-Desktop_Qt_5_15_2_GCC_64bit-Debug" -lMathFunies



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
