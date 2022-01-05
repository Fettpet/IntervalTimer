import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root

    required property var planRunner
    signal stopRunning

    ColumnLayout {
        Text {
            text: "Interval-Name: " + planRunner.intervalDescription
        }
        Text {
            text: "Time: " + planRunner.intervalDurationRunningTime + "/"
                  + planRunner.intervalDurationCompleteTime
        }

        Button {
            text: "stop"
            onClicked: root.stopRunning()
        }
    }
}
