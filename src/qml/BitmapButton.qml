import QtQuick 2.10

Rectangle {
    property string icon: ""
    property string pressedIcon: ""
    property string disabledIcon: ""
    property string normalColor: "white"
    property string pressedColor: "white"
    property bool pushable: false
    property alias verticalAlignment: img.verticalAlignment
    property int holdInterval: 700

    id: btn
    implicitWidth: img.implicitWidth
    implicitHeight: img.implicitHeight

    Image {
        id: img
        source: btn.icon
        anchors.verticalCenter: btn.verticalCenter
        anchors.horizontalCenter: btn.horizontalCenter
        z: 2
    }

    Timer {
        id: hold_timer
        property int holdCounter: 0
        interval: holdInterval
        repeat: true
        running: false
        triggeredOnStart: true
        onTriggered: {
            holdCounter++;
            hold(holdCounter);
        }
    }

    state: "Normal"
    signal action
    signal hold(int counter)
    states: [
        State {
            name: "Normal"; when: img.enabled
            PropertyChanges { target: btn; color: btn.normalColor }
            PropertyChanges { target: img; source: btn.icon }
        },
        State {
            name: "Pressed"; when: img.enabled
            PropertyChanges { target: btn; color: btn.pressedColor }
            PropertyChanges { target: img; source: btn.pressedIcon }
        },
        State {
            name: "Disabled"; when: !img.enabled
            PropertyChanges { target: btn; color: btn.normalColor }
            PropertyChanges { target: img; source: btn.disabledIcon }
        }
    ]

    MouseArea {
        anchors.fill: btn
        onPressed: {
            hold_timer.holdCounter = 0;
            btn.state = "Pressed"
            if (pushable) {
                btn.action()
            }
        }
        onReleased: {
            if (!pushable && btn.state == "Pressed") {
                btn.state = "Normal"
                if (hold_timer.holdCounter === 0)
                    btn.action()
            }
            if (hold_timer.running)
                hold_timer.stop()
        }
        onPressAndHold: {
            if (!pushable) {
                hold_timer.start();
            }
        }
        onExited: {
            if (!pushable && btn.state !== "Disabled") {
                btn.state = "Normal"
            }
            if (hold_timer.running)
                hold_timer.stop()
        }
        onCanceled: {
            if (!pushable && btn.state !== "Disabled") {
                btn.state = "Normal"
            }
            if (hold_timer.running)
                hold_timer.stop()
        }
        z: 3
    }
    Keys.onPressed: {
        if (event.key === Qt.Key_Enter)
        {
            btn.state = "Pressed"
            if (pushable) {
                btn.action()
            }
        }
        else
            event.accepted = false;
    }
    Keys.onReleased: {
        if (event.key === Qt.Key_Enter)
        {
            if (!pushable) {
                btn.state = "Normal"
                btn.action()
            }
        }
        else
            event.accepted = false;
    }
}
