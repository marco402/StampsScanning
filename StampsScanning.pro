#-------------------------------------------------
#
# Project created by QtCreator 2020-05-29T12:41:21
#
#-------------------------------------------------

QT       += core gui
QT       += help
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StampsScanning
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11



SOURCES += \
    main.cpp \
    presentation/class_functions_windows.cpp \
    presentation/form_help.cpp \
    presentation/form_main.cpp \
    presentation/form_stamp.cpp \
    presentation/helpBrowser.cpp \
    presentation/partial_form_main_command.cpp \
    presentation/partial_form_main_resizeform.cpp \
    presentation/partial_form_main_setting.cpp \
    presentation/partial_form_main_translate.cpp \
    process/class_generiques_fonctions.cpp \
    process/class_geometrie.cpp \
    process/class_one_stamp_generales_functions.cpp \
    process/class_perforation.cpp \
    process/class_scan_border.cpp \
    process/class_sep_stamps_find_borders.cpp \
    process/class_sep_stamps_generales_functions.cpp \
    process/class_sep_stamps_thread.cpp \
    process/partial_form_main_manage_separate_stamps_thread.cpp \

HEADERS += \
    common.h \
    constantes.h \
    presentation/class_functions_windows.h \
    presentation/form_help.h \
    presentation/form_main.h \
    presentation/form_stamp.h \
    presentation/helpBrowser.h \
    process/class_generiques_fonctions.h \
    process/class_geometrie.h \
    process/class_one_stamp_generales_functions.h \
    process/class_perforation.h \
    process/class_scan_border.h \
    process/class_sep_stamps_find_borders.h \
    process/class_sep_stamps_generales_functions.h \
    process/class_sep_stamps_thread.h \

TRANSLATIONS = languages/stampscanning_en.ts languages/stampscanning_fr.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    bitmap.qrc

# only for unix system.

DISTFILES += \
    README.md \
    languages/en.png \
    languages/fr.png \
    languages/stampscanning_en.qm \
    languages/stampscanning_en.ts \
    languages/stampscanning_fr.qm \
    languages/stampscanning_fr.ts \
    todo




