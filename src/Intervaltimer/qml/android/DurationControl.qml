import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root
    required property int duration
    readonly property int seconds: duration % 60
    readonly property int minutes: (duration / 60) % 60
    readonly property int hours: (duration / 3600)

    function zeroPad(num, places) {
        return String(num).padStart(places, '0')
    }
    contentItem: TextField {
        id: displayTime
        background: Rectangle {
            color: "transparent"
        }

        readOnly: true
        readonly property string displayText: hours + ":" + zeroPad(
                                                  minutes,
                                                  2) + ":" + zeroPad(seconds, 2)
        text: duration != 0 ? displayText : ""
        placeholderText: duration == 0 ? displayText : ""
        MouseArea {
            anchors.fill: parent
            onClicked: {
                designer.open()
                focus = true
            }
        }
        Popup {
            id: designer
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
            parent: Overlay ? Overlay.overlay : undefined
            anchors.centerIn: parent
            ColumnLayout {
                RowLayout {
                    DurationTumbler {
                        id: hoursTumbler
                        model: 24
                        currentIndex: root.hours
                    }
                    DurationTumbler {
                        id: minutesTumbler
                        model: 60
                        currentIndex: root.minutes
                    }
                    DurationTumbler {
                        id: secondTumbler
                        model: 60
                        currentIndex: root.seconds
                    }
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    RoundButton {
                        text: "OK"
                        onClicked: designer.close()
                    }
                    RoundButton {
                        text: "Cancel"
                        onClicked: {
                            hoursTumbler.currentIndex = root.hours
                            minutesTumbler.currentIndex = root.minutes
                            secondTumbler.currentIndex = root.seconds
                            designer.close()
                        }
                    }
                }
            }
            onClosed: {
                root.duration = hoursTumbler.currentIndex * 3600
                        + minutesTumbler.currentIndex * 60 + secondTumbler.currentIndex
            }
        }
    }
}
