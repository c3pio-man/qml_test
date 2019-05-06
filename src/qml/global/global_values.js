Qt.include("global.js")

// eink-reader

var minimalLineHeight = 1
var minimalLineThickness = 1
var separatorSideOffset = dp(18)
var separatorMenuSideOffset = dp(5)

var headerHeight = dp(DeviceInfoProvider.isTouchDevice ? 56 : 46.8) + minimalLineHeight
var headerTitleFontSize = 8

var defaultListItemHeight = DeviceInfoProvider.isTouchDevice ? dp(54) + minimalLineHeight : dp(67) + minimalLineHeight

//var defaultBorderThickness = dp(3);

var scrollListButtonsWidth = dp(71);
var scrollListButtonsHeight = dp(56);
var scrollListCenterButtonSideOffset = scrollListButtonsWidth + dp(22);

var defaultFontSize = 8

// other

var defaultAppHeaderHeight = dp(56)
var defaultAppHeaderMargin = dp(15)
var defaultAppHeaderFontSize = 8

var defaultSolidSeparatorThickness = 1
var defaultSolidseparatorColor = "black"

var defaultTabsPanelHeight = dp(56)
var defaultTabsPanelSelectedTabIndicatorHeight = 7
var defaultTabsPanelFontSize = 8

var defaultAudioControlPanelHeight = dp(66)

var defaultFolderSelectDialogOffset = dp(12);
var defaultFolderSelectDialogSideMargin = dp(38);

var defaultInputDialogWidth = dp(450);
var defaultInputDialogOffset = dp(135);

var defaultInfoMessageHeight = dp(184)
var defaultInfoMessageWidth = dp(450)
var defaultInfoMessageFontSize = 8

var defaultPressedFrameBorderWidth = 3

var defaultSaveFileDialogVerticalOffset = dp(100)

var defaultTextEditAreaHeigth = 3 * defaultListItemHeight / 2

var defaultTreeLineElementThickness = 1
var defaultTreeLineElementColor = "black"

var defaultButtonFontSize = 8
var defaultTextInputFontSize = 8

var defaultBorderThickness = 5;
var defaultTextButtonHeight = dp(52);
var defaultListViewSideMargin = dp(24);
var defaultListViewSidePadding = dp(12);

var defaultDialogWidth = dp(500);
var defaultDialogVerticalOffset = dp(56) + dp(12);
var dialogHeaderHeight = dp(56);
var dialogHeaderSeparatorSideOffset = dp(15);
var dialogHeaderSideOffset = dp(22);
var dialogBottomButtonsHeight = dp(56);

var defaultMenuMargin = dp(4.5);

var headerLeftMargin = dp(15);

var fileSelectDialogMargin = dp(20);
var fileSelectDialogSideMargin = dp(38);
var fileSelectDialogTopMargin = dp(12);
var fileSelectDialogBottomMargin = dp(12);

var playbackControlDialogWidth = dp(480);
var playbackControlDialogInnerHeight = dp(114);

var managePlaylistsDialogWidth = dp(480);
var managePlaylistsDialogInnerHeight = 6 * (defaultTextButtonHeight + defaultSolidSeparatorThickness);

var audioBooksPlaybackControlDialogWidth = dp(480);
var audioBooksPlaybackControlDialogInnerHeight = dp(228);

var autoShutdownDialogWidth = defaultDialogWidth;
var autoShutdownDialogHeight = 7 * (defaultTextButtonHeight + defaultSolidSeparatorThickness);

var confirmationDialogWidth = dp(500);
var confirmationDialogInnerHeight = dp(178);
var confirmationDialogVerticalOffset = defaultAppHeaderHeight;

var equalizerDialogWidth = dp(500);
var equalizerDialogInnreHeight = dp(480);

var aboutTrackDialogWidth = dp(480);

var treeViewFileSystemHeight = dp(480);

var dialogSideMargin = dp(38);
var dialogSidePadding = dp(30);
var dialogBorderWidth = 7

var scrollerThinLineThickness = dp(1.6)
var scrollerThickLineThickness = 2 * scrollerThinLineThickness + (scrollerThinLineThickness % 2) // dp(3.73)

var headerBackButtonMargin = dp(7.5)
var headerSearchWrapperBorderWidth = 1

var progressBarHeight = dp(6)

var scrollIndicatorThickness = dp(4)
var minimalScrollIndicatorThickness = dp(25)
var scrollIndicatorSideMargin = dp(2)
