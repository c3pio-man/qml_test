# qml_test example application


This application is an example qt qml application for Pocketbook device

This example uses some Pocketbook specific functionality:

- It uses pocketbook2 platform plugin to allow application to run on device or emulator
- Class DeviceInfoProvider contains useful device specific info (like screen size in pixels) and opens for qml some of EinkPlatformInterface functionality (e.g., managing screen update types)
- Class EinkPlatformInterface contains functions needed to communicate with platform plugin to access some eink specific functionality (this class is defined in the common_utilities/einkinterface.h file in SDK includes)
- Class PBTranslator provide access to localization which used in firmware (used in standard components)
- Class ResourceImageProvider provide access to themes icons used in firmware (used in standard components)


# Screen updates.

Eink screen has some specific features, which should be taken into consideration while programming for PocketBook device. It takes a long time to update screen (it is possible to make only few full screen updates in a second) and there are several types of screen updates, which differ in quality, functionality and speed. In EinkPlatformInterface class were defined several update types. Here are the most useful of them:

- Full - it is a very long and high quality update, which first turns all screen pixels to black and than to requested colors. This update always takes the whole screen. It could be used to obtain a good picture without "dirt" (pixels, which are not as white as they should be on image) and "artifacts" (traces from the previous picture drawn on screen), but it takes a long time and blinks screen with black. It is not good idea to use it every time. For example in pocketbook reader application it is used once to 5 or 10 screens (actually it is configurable) to achieve trade-off between quality and speed. To use this update EinkPlatformInterface::requireFullUpdate function should be used.
- Partial - it is a default update for pocketbook2 platform plugin (no need to specially set this update). It can be used on rectangular part of the screen. The smaller update area needs the less time for update. This update is quicker than Full update and screen doesn't blink during this update, but after several updates some "dirt" and "artifacts" could appear.
- Dynamic - it is more quicker than partial. It could be used for example during typing text in text inputs. To use this update once - the EinkPlatformInterface::requireUpdateType function should be used with UpdateType::Dynamic as a parameter. To go into entering text mode EinkPlatformInterface::setQuickKeyboardEnterUpdateMode should be used (in this mode all updates are Dynamic by default).

Also there is an update mode called A2. It is the fastest update (up to ~8 updates per second) but it supports only 2 colors (black and white) and needs a  special procedure to enter/exit this update mode. It should be used when update speed is critical (e.g. for scroll, pinch to zoom, animations). To enter this mode the following methods can be used: EinkPlatformInterface::enterA2ForRegion, EinkPlatformInterface::a2ForFlick or EinkPlatformInterface::a2ForPinch. They should be used for animation, scrolling and pinch-to-zoom accordingly. To exit this mode EinkPlatformInterface::leaveA2 or EinkPlatformInterface::timedLeaveA2 should be used.

Sometimes the program needs to do several changes on the screen but for user these changes should be presented in one update. In such cases EinkPlatformInterface::setAllowRedraw or EinkPlatformInterface::setAllowRedrawEx function can be used to disable updates, then do all necessary changes and then enable updates again.
