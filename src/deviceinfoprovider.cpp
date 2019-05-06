#include "deviceinfoprovider.h"
#include <inkview.h>
#include <inkinternal.h>
#include <inkplatform.h>

using namespace pocketbook::utils;
using namespace pocketbook::utilities;

DeviceInfoProvider &DeviceInfoProvider::Instance()
{
    static DeviceInfoProvider *this_ = nullptr;
    if (!this_)
    {
        this_ = new DeviceInfoProvider();
    }
    return *this_;
}

DeviceInfoProvider::DeviceInfoProvider()
{
}

DeviceInfoProvider::~DeviceInfoProvider()
{
}

int DeviceInfoProvider::screenWidth() const
{
    return ::ScreenWidth();
}

int DeviceInfoProvider::screenHeight() const
{
    return ::ScreenHeight();
}

int DeviceInfoProvider::panelHeight() const
{
    return ::PanelHeight();
}

bool DeviceInfoProvider::isSDInserted() const
{
    return bool(::IsSDinserted());
}

QUrl DeviceInfoProvider::userRootFolder() const
{
#ifdef EMULATOR
    return QUrl("file:system/mnt");
#else
    return QUrl("file:///mnt");
#endif
}

bool DeviceInfoProvider::isEmulator() const
{
#ifdef EMULATOR
    return true;
#else
    return false;
#endif
}

void DeviceInfoProvider::enterA2onFlick(int x, int y, int w, int h)
{
    irect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    einkPlatform()->a2ForFlick(rect);
}

void DeviceInfoProvider::enterA2onPinch(int x, int y, int w, int h)
{
    irect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    einkPlatform()->a2ForPinch(rect);
}

void DeviceInfoProvider::enterA2forRegion(int x, int y, int w, int h)
{
    irect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    einkPlatform()->enterA2ForRegion(rect);
}

void DeviceInfoProvider::exitA2()
{
    einkPlatform()->leaveA2();
}

bool DeviceInfoProvider::isInA2()
{
    return einkPlatform()->isInA2();
}

bool DeviceInfoProvider::createNewFolder(QString folder_name)
{
    QUrl folder(folder_name);
    folder.setScheme("");
    return QDir().mkpath(folder.url());
}

void DeviceInfoProvider::notToSleepFor(int sec)
{
    ::BanSleep(sec);
}

static int noSleepCounter = 0;
static void noSleepTimerCallback() {
    if (noSleepCounter > 0) {
        --noSleepCounter;
        SetHardTimer("NoSleepTimer", &noSleepTimerCallback, 100);
    }
}

void DeviceInfoProvider::doNotSleep(int timeout_ms)
{
    if (noSleepCounter < timeout_ms / 100)
        noSleepCounter = timeout_ms / 100;
    SetHardTimer("NoSleepTimer", &noSleepTimerCallback, 100);
}

QString DeviceInfoProvider::getPrettifiedFilePath(QString file_path)
{
    QString pretty_file_path = file_path;
    QString needle = QString(FLASHDIR);
    int position = file_path.indexOf(needle);
    if(position >= 0) {
        pretty_file_path = QString(GetLangText("@DeviceMemory")) + file_path.right(file_path.length() - position - needle.length());
    } else {
        needle = QString(SDCARDDIR);
        position = file_path.indexOf(needle);
        if(position >= 0) {
            pretty_file_path = QString(GetLangText("@SDcard")) + file_path.right(file_path.length() - position - needle.length());
        }
    }
    return pretty_file_path;
}

void DeviceInfoProvider::rescanFolder(QString folder_path)
{
    int scanner_task = ::FindTaskByAppName("/ebrmain/bin/scanner.app");
    if (-1 != scanner_task) {
        std::string data = "-scan:" + folder_path.toStdString();
        ::SendRequestTo(scanner_task, REQ_OPENBOOK, (void*)data.c_str(), data.size(), 0, 2000);
    }
}

int DeviceInfoProvider::getDpi()
{
    if (dpi_ == -1)
        dpi_ = get_screen_dpi();
    return dpi_;
}

double DeviceInfoProvider::getScaleFactor()
{
    if (scale_factor_ == -1)
        scale_factor_ = get_screen_scale_factor();
    return scale_factor_;
}

bool DeviceInfoProvider::isTouchDevice()
{
    bool res = HWC_FINGERS_TOUCHPANEL;
    return res;
}

bool DeviceInfoProvider::isSupportFrontlight()
{
    bool res = HWC_FRONTLIGHT;
#ifdef EMULATOR
    res = 1;
#endif
    return res;
}

bool DeviceInfoProvider::isSupportFrontlightColor()
{
    bool res = HWC_FRONTLIGHT == FRONTLIGHT_DUAL;
#ifdef EMULATOR
    res = true;
#endif
    return res;
}

void DeviceInfoProvider::initFrontlightValue()
{
    if (frontlight_value_ == -1)
    {
        iconfig *cfg = OpenConfig(GLOBALCONFIGFILE, NULL);
        frontlight_value_ = ReadInt(cfg, "FrontLightLastState", 60);
        CloseConfigNoSave(cfg);
    }
}

int DeviceInfoProvider::getFrontlightValue()
{
    initFrontlightValue();
    return frontlight_value_;
}

void DeviceInfoProvider::setFrontlightValue(int value)
{
    if (value != -1)
    {
        frontlight_value_ = value;
        SetFrontlightState(value);
        is_frontlight_value_changed_ = true;
    }
    else
    {
        SetFrontlightState(value);
    }
}

int DeviceInfoProvider::getFrontlightState()
{
    int state = GetFrontlightState() == -1 ? 0 : 1;
#ifdef EMULATOR
    state = frontlight_state_;
#endif
    return state;
}

void DeviceInfoProvider::setFrontlightState(int state)
{
    if (state)
    {
        initFrontlightValue();
        SetFrontlightState(frontlight_value_);
    }
    else
    {
        SetFrontlightState(-1);
    }
#ifdef EMULATOR
    frontlight_state_ = state;
#endif
}

void DeviceInfoProvider::saveFrontlightValue()
{
    initFrontlightValue();
    if (is_frontlight_value_changed_)
    {
        iconfig *cfg = OpenConfig(GLOBALCONFIGFILE, NULL);
        WriteInt(cfg, "FrontLightLastState", frontlight_value_);
        CloseConfig(cfg);
        is_frontlight_value_changed_ = false;
    }
}

bool DeviceInfoProvider::hasAudio()
{
#ifdef EMULATOR
    return true;
#else
    bool res = HWC_AUDIO;
    if (res)
    {
        iconfig *cfg = OpenConfig(SYSTEMDATA"/config/device.cfg", NULL);
        int res = ReadInt(cfg, "have_tts", 0);
        CloseConfigNoSave(cfg);
        return res == 0 ? false : true ;
    }
    return res;
#endif
}

int DeviceInfoProvider::getScreenWidth()
{
    return ::ScreenWidth();
}

int DeviceInfoProvider::getScreenHeight()
{
    return ::ScreenHeight();
}

int DeviceInfoProvider::getPanelHeight() {
    return ::PanelHeight();
}

bool DeviceInfoProvider::isSupportGSensor()
{
    return HWC_HAS_GSENSOR;
}
