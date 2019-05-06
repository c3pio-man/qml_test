import QtQuick 2.10
import "global/global_values.js" as GlobalValues

Rectangle {
    id: app_header
    height: GlobalValues.defaultAppHeaderHeight

    property alias title: title_text.text
    property bool canMinimize: false

    property alias minimizeIcon: minimize_button.icon
    property alias minimizePressedIcon: minimize_button.pressedIcon

    property alias closeIcon: close_button.icon
    property alias closePressedIcon: close_button.pressedIcon

    signal close
    signal minimize

    BitmapButton {
        id: close_button
        anchors.left: parent.left
        anchors.leftMargin: GlobalValues.defaultAppHeaderMargin
        anchors.verticalCenter: parent.verticalCenter
        icon: "image://resource/home"
        pressedIcon: "image://resource/home_inv"
        onAction: {
            app_header.close()
        }
    }

    Text {
        id: title_text
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        elide: Text.ElideRight
        font.pointSize: GlobalValues.defaultFontSize
        font.capitalization: Font.AllUppercase
    }

    BitmapButton {
        id: minimize_button
        anchors.right: parent.right
        anchors.rightMargin: GlobalValues.defaultAppHeaderMargin
        anchors.verticalCenter: parent.verticalCenter
        icon: ""
        pressedIcon: ""
        visible: app_header.canMinimize
        onAction: {
            app_header.minimize()
        }
    }
}
