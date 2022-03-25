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
    ColumnLayout {

        ProgressView {
            textColor: root.textColor
            backgroundColor: root.backgroundColor
            minimumValueInner: 0
            maximumValueInner: PlanRunner.intervalDurationCompleteTime
            currentValueInner: PlanRunner.intervalDurationRunningTime
            minimumValueOuter: 0
            maximumValueOuter: PlanRunner.planDurationCompleteTime
            currentValueOuter: PlanRunner.planDurationRunningTime

            text: PlanRunner.intervalDescription
        }

        Button {
            text: "Stop"
            onClicked: root.stopRunning()
        }
    }
}
