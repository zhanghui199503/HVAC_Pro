QT += core gui axcontainer printsupport serialport sql printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QXlsx/QXlsx.pri)
INCLUDEPATH += $$PWD QXlsx

CONFIG += resources_big
CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MFormMotor.cpp \
    RFID/mRFID_Dialog.cpp \
    aboutsoftware.cpp \
    communicationerror.cpp \
    datasetting.cpp \
    editablelabel.cpp \
    home_interface.cpp \
    hvac_mode.cpp \
    ini_file.cpp \
    lin_dataset.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    manualui.cpp \
    motor_dataset.cpp \
    plc_mc.cpp \
    pop_ups_alarm.cpp \
    pop_ups_ng.cpp \
    pop_ups_ok.cpp \
    serialportworker.cpp \
    showpicture.cpp \
    systemdataset.cpp \
    thread_CommTask.cpp \
    thread_main.cpp \
    thread_ptmotor.cpp

HEADERS += \
    Header_File.h \
    MFormMotor.h \
    RFID/mRFID_Dialog.h \
    aboutsoftware.h \
    communicationerror.h \
    datasetting.h \
    editablelabel.h \
    home_interface.h \
    hvac_mode.h \
    ini_file.h \
    lin_dataset.h \
    login.h \
    mainwindow.h \
    manualui.h \
    motor_dataset.h \
    motor_types.h \
    plc_mc.h \
    pop_ups_alarm.h \
    pop_ups_ng.h \
    pop_ups_ok.h \
    serialportworker.h \
    showpicture.h \
    systemdataset.h \
    thread_CommTask.h \
    thread_main.h \
    thread_ptmotor.h

FORMS += \
    MFormMotor.ui \
    RFID/mRFID_Dialog.ui \
    aboutsoftware.ui \
    communicationerror.ui \
    datasetting.ui \
    home_interface.ui \
    hvac_mode.ui \
    lin_dataset.ui \
    login.ui \
    mainwindow.ui \
    manualui.ui \
    motor_dataset.ui \
    plc_mc.ui \
    pop_ups_alarm.ui \
    pop_ups_ng.ui \
    pop_ups_ok.ui \
    showpicture.ui \
    systemdataset.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pritrue.qrc

RC_ICONS = SONGZ_ICO.ico

