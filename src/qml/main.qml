import QtQuick 2.8
import QtQuick.Window 2.2

import "global/global.js" as Global

Window {

    width: DeviceInfoProvider.screenWidth

    height: DeviceInfoProvider.screenHeight - DeviceInfoProvider.panelHeight
    visible: true

    AppHeader {
        id: app_header
        title: "Test application"
        minimizeIcon: "image://resource/player2_minimize"
        minimizePressedIcon: "image://resource/player2_minimize_inv"
        canMinimize: false
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        onClose: {
            DataManager.close();
        }
    }
    Rectangle {
        id: sepatator
        anchors.top: app_header.bottom
        height:  1
        width: parent.width
        color: "black"
    }

    ListModel {
        id: testModel

        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 1"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 2"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 3"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 4"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 5"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 6"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 7"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 8"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 9"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 10"
        }
        ListElement {
            icon: "image://resource/e3_list_reader"
            text: "Test item 11"
        }
    }

    ListView {
        id: list
        anchors.top: sepatator.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        model: testModel
        clip: true
        delegate: Rectangle {
            id: list_item
            width: parent.width
            height: childrenRect.height

            Column {
                anchors.left: parent.left
                anchors.leftMargin: Global.dp(12)
                anchors.right: parent.right
                anchors.rightMargin: Global.dp(12)
                Row {
                    height: Global.dp(72)
                    Image {
                        id: im
                        anchors.verticalCenter: parent.verticalCenter
                        source: icon

                    }
                    Text {
                        id: txt
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        text: model.text
                        font.pointSize: 8
                    }
                }
                Rectangle {
                    id: sepatator1
                    height:  1
                    width: parent.width
                    color: "black"
                }
            }
        }

        ScrollBar {
            id: scroll_bar
            element: list
            z: 1
        }

        onMovementStarted: {
            var coords = list.mapToGlobal(0, 0)
            DeviceInfoProvider.enterA2onFlick(coords.x, coords.y, list.width, list.height)
        }
        onMovementEnded: {
            DeviceInfoProvider.exitA2()
        }

    }

}
