#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextCodec>
#include <inkview.h>
#include "deviceinfoprovider.h"
#include "resourceimageprovider.h"
#include "pbtranslator.h"
#include "datamanager.h"


int main(int argc, char *argv[])
{
    setenv("QT_QPA_PLATFORM", "pocketbook2", 1);

    QGuiApplication app(argc, argv);

#ifndef EMULATOR
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);
#endif

    app.installTranslator(new pocketbook::utils::PBTranslator());

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("DeviceInfoProvider", &pocketbook::utils::DeviceInfoProvider::Instance());
    DataManager dataManager;
    engine.rootContext()->setContextProperty("DataManager", &dataManager);

    engine.addImageProvider("resource", new pocketbook::utils::ResourceImageProvider());
    engine.addImageProvider("resource_inv", new pocketbook::utils::ResourceImageProvider(true));

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));


    return app.exec();
}
