import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Pane {
    id: root
    property color backgroundColor: "#222222"
    property color textColor: "red"
    signal stopRunning
    background: Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
    }

    Text {
        id: textRunningTime

        readonly property int value: (PlanRunner.planDurationCompleteTime
                                      - PlanRunner.planDurationRunningTime) / 1000
        readonly property bool showMinutes: PlanRunner.planDurationCompleteTime > (60 * 1000)
        readonly property bool showHours: PlanRunner.planDurationCompleteTime > (60 * 60 * 1000)
        readonly property int seconds: value % 60
        readonly property int minutes: (value / 60) % 60
        readonly property int hours: (value / 3600)
        readonly property string formatedText: {
            if (showHours)
                return hours + ":" + zeroPad(minutes,
                                             2) + ":" + zeroPad(seconds, 2)
            if (showMinutes)
                return minutes + ":" + zeroPad(seconds, 2)
            return seconds
        }

        function zeroPad(num, places) {
            return String(num).padStart(places, '0')
        }

        anchors.bottom: progress.top
        anchors.horizontalCenter: progress.horizontalCenter
        color: root.textColor
        anchors.margins: 20
        text: "Remaining Time: " + formatedText
    }

    ProgressView {
        id: progress
        textColor: root.textColor
        anchors.centerIn: parent
        backgroundColor: root.backgroundColor
        minimumValueInner: 0
        maximumValueInner: PlanRunner.intervalDurationCompleteTime
        currentValueInner: PlanRunner.intervalDurationRunningTime
        minimumValueOuter: 0
        maximumValueOuter: PlanRunner.planDurationCompleteTime
        currentValueOuter: PlanRunner.planDurationRunningTime

        text: PlanRunner.intervalDescription
    }

    RowLayout {
        anchors.horizontalCenter: progress.horizontalCenter
        anchors.top: progress.top
        anchors.topMargin: progress.height / 2 + 30
        RoundButton {
            radius: width / 2
            text: "Back"
            onClicked: root.stopRunning()
        }

        RoundButton {
            id: rerunButton
            visible: false
            enabled: visible
            radius: width / 2
            text: "Rerun"
            onClicked: PlanRunner.start()
        }

        Connections {
            target: PlanRunner
            function onFinished() {
                rerunButton.visible = true
                progress.text = "Finished"
            }
        }

        Connections {
            target: PlanRunner
            function onStartRunning() {
                rerunButton.visible = false
            }
        }
    }
}
