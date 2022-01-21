import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root

    signal stopRunning

    ColumnLayout {
        Text {
            text: "Interval-Name: " + PlanRunner.intervalDescription
        }
        Text {
            text: "Interval-Time: " + PlanRunner.intervalDurationRunningTime
                  + "/" + PlanRunner.intervalDurationCompleteTime
        }
        Text {
            text: "Plan-Time: " + PlanRunner.planDurationRunningTime + "/"
                  + PlanRunner.planDurationCompleteTime
        }

        Button {
            text: "stop"
            onClicked: root.stopRunning()
        }
    }
}
