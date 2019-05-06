#ifndef DEVICEINFOPROVIDER_H
#define DEVICEINFOPROVIDER_H


#include <inkview.h>
#include <common_utilities/einkinterface.h>

#include <QObject>
#include <QUrl>
#include <QDir>

namespace pocketbook { namespace utils {

class DeviceInfoProvider : public QObject
{
    Q_OBJECT
public:
    static DeviceInfoProvider &Instance();
    ~DeviceInfoProvider();

    Q_PROPERTY(bool isTouchDevice READ isTouchDevice NOTIFY isTouchDeviceChanged)
    Q_PROPERTY(bool hasAudio READ hasAudio NOTIFY hasAudioChanged)
    Q_PROPERTY(bool isSDInserted READ isSDInserted NOTIFY isSDInsertedChanged)

    Q_PROPERTY(bool isSupportFrontlight READ isSupportFrontlight)
    Q_PROPERTY(bool isSupportFrontlightColor READ isSupportFrontlightColor)
    Q_PROPERTY(int frontlightValue READ getFrontlightValue WRITE setFrontlightValue)
    Q_PROPERTY(int frontlightState READ getFrontlightState WRITE setFrontlightState)

    Q_PROPERTY(int screenWidth READ screenWidth NOTIFY screenWidthChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY screenHeightChanged)
    Q_PROPERTY(int panelHeight READ panelHeight NOTIFY panelHeightChanged)

    Q_PROPERTY(QUrl userRootFolder READ userRootFolder NOTIFY userRootFolderChanged)

    int screenWidth() const;
    int screenHeight() const;

    int panelHeight() const;

    bool isSDInserted() const;

    QUrl userRootFolder() const;

signals:
    void isTouchDeviceChanged();
    void hasAudioChanged();
    void screenWidthChanged();
    void screenHeightChanged();
    void panelHeightChanged();
    void isSDInsertedChanged(bool isSDInserted);

    void userRootFolderChanged(QUrl userRootFolder);

public slots:
    int getDpi();
    double getScaleFactor();
    bool isTouchDevice();
    bool hasAudio();
    bool isSupportFrontlight();
    bool isSupportFrontlightColor();
    void initFrontlightValue();
    int getFrontlightValue();
    void setFrontlightValue(int value);
    int getFrontlightState();
    void setFrontlightState(int state);
    void saveFrontlightValue();
    int getScreenWidth();
    int getScreenHeight();
    int getPanelHeight();
    bool isSupportGSensor();
    bool isEmulator() const;
    void enterA2onFlick(int x, int y, int w, int h);
    void enterA2onPinch(int x, int y, int w, int h);
    void enterA2forRegion(int x, int y, int w, int h);
    void exitA2();
    bool isInA2();
    bool createNewFolder(QString folder_name);
    void notToSleepFor(int sec);
    void doNotSleep(int ms);
    QString getPrettifiedFilePath(QString file_path);
    void rescanFolder(QString folder_path);

private:
    DeviceInfoProvider();

    int dpi_ = -1;
    double scale_factor_ = -1;

    int frontlight_value_ = -1;
    bool is_frontlight_value_changed_ = false;

#ifdef EMULATOR
    int frontlight_state_ = 1;
#endif // EMULATOR
};

}} // namespace

#endif // DEVICEINFOPROVIDER_H
