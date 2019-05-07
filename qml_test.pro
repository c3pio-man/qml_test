TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/deviceinfoprovider.cpp \
    src/resourceimageprovider.cpp \
    src/pbtranslator.cpp \
    datamanager.cpp

RESOURCES += src/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SYSROOT=$$(PB_SYSROOT)
message(SYSROOT dir is $$SYSROOT )

contains (PLATFORM, arm) {
    message(arm)


    LIBS += -linkview -lcommon_utilities  -lhwconfig
    LIBS += -ljsoncpp -ldl -lz -lcrypto
    INCLUDEPATH += $$SYSROOT/usr/include $$SYSROOT/usr/local/include $$SYSROOT/usr/include/freetype2 $$SYSROOT/usr/include/jsoncpp ../src
    message("INCLUDEPATH = $$INCLUDEPATH")


} else {
    message(linux)
    message("PB_SDK_DIR="$$(PB_SDK_DIR))

    CONFIG += link_pkgconfig
    PKGCONFIG += freetype2
    DEFINES += "EMULATOR=1"
    LIBS += -L$$(PB_SDK_DIR)/usr/lib -L$$(PB_SDK_DIR)/usr/local/lib -lcommon_utilities -ljpeg -linkview -lhwconfig
    INCLUDEPATH += $$(PB_SDK_DIR)/usr/local/include $$(PB_SDK_DIR)/usr/include /usr/include/jsoncpp $$PWD/src
}

HEADERS += \
    src/deviceinfoprovider.h \
    src/resourceimageprovider.h \
    src/pbtranslator.h \
    datamanager.h

DISTFILES +=
