QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20\

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dif_level.cpp \
    gra.cpp \
    hint.cpp \
    licznik.cpp \
    login_window.cpp \
    login_window_edit.cpp \
    login_window_reg.cpp \
    main.cpp \
    main_window.cpp \
    mistakes.cpp \
    my_button.cpp \
    notatki.cpp \
    savegame.cpp \
    sudoku.cpp \
    user.cpp

HEADERS += \
    dif_level.h \
    gra.h \
    hint.h \
    licznik.h \
    login_window.h \
    login_window_edit.h \
    login_window_reg.h \
    main_window.h \
    mistakes.h \
    my_button.h \
    notatki.h \
    savegame.h \
    sudoku.h \
    user.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    Tex.qrc

DISTFILES +=
