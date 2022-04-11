import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Desctop

Frame {
    id: root

    signal stopRunning

    ColumnLayout {

        ProgressView {
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
