import QtQuick 2.10
import "global/global.js" as Global
import "global/global_values.js" as Values

Item {
    id: scroll_bar

    property Flickable element

    state: "Vertical"

    states: [
        State {
            name: "Horizontal"
            PropertyChanges {
                target: scroll_bar
                width: element.width
                height: Global.dp(4)
                anchors.rightMargin: undefined
                anchors.bottomMargin: Global.dp(2)
            }
            AnchorChanges {
                target: scroll_bar
                anchors.left: element.left
                anchors.right: element.right
                anchors.top: undefined
                anchors.bottom:  element.bottom
            }
            PropertyChanges {
                target: scroller_rect
                y: 0
                x: Math.min(scroll_bar.width - scroller_rect.width,
                            (scroll_bar.width - scroller_rect.width) * element.contentX / Math.max(element.contentWidth - element.width, 1))
                width:  Math.max(scroll_bar.width * element.width / element.contentWidth, Global.dp(25))
                height: scroll_bar.height
                visible: element.contentWidth > element.width
            }
        },
        State {
            name: "Vertical"
            PropertyChanges {
                target: scroll_bar
                width: Global.dp(4)
                height: element.height
                anchors.rightMargin: Global.dp(2)
                anchors.bottomMargin: undefined
            }
            AnchorChanges {
                target: scroll_bar
                anchors.left: undefined
                anchors.right: element.right
                anchors.top: element.top
                anchors.bottom:  element.bottom
            }
            PropertyChanges {
                target: scroller_rect
                y: Math.min(scroll_bar.height - scroller_rect.height,
                            (scroll_bar.height - scroller_rect.height) * element.contentY / Math.max(element.contentHeight - element.height, 1))
                x: 0
                width: scroll_bar.width
                height: Math.max(scroll_bar.height * element.height / element.contentHeight, Global.dp(25))
                visible: element.contentHeight > element.height
            }
        }
    ]

    width: Global.dp(4)
    height: element.height
    anchors.right: element.right
    anchors.rightMargin: Global.dp(2)
    anchors.top: element.top
    anchors.bottom:  element.bottom

    Rectangle {
        id: scroller_rect
        y: Math.min(scroll_bar.height - scroller_rect.height,
                    (scroll_bar.height - scroller_rect.height) * element.contentY / Math.max(element.contentHeight - element.height, 1))
        x: 0
        width: scroll_bar.width
        height: Math.max(scroll_bar.height * element.height / element.contentHeight, Global.dp(25))
        color: "black"
        visible: element.contentHeight > element.height
    }
}

