import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

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
            text: "stop"
            onClicked: root.stopRunning()
        }
    }
}
