QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    menu.cpp \
    persowindow.cpp \
    rendezvous.cpp \
    src/Appointment.cpp \
    src/Date.cpp \
    src/Horaire.cpp \
    src/Personne.cpp \
    src/Rdv.cpp \
    src/customrdv.cpp \
    src/personnes.cpp

HEADERS += \
    include/Appointment.h \
    include/Date.h \
    include/Horaire.h \
    include/Personne.h \
    include/Rdv.h \
    include/personnes.h \
    menu.h \
    persowindow.h \
    rendezvous.h \
    src/customrdv.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    download.png
