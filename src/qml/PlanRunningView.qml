import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root

    required property var planModel
    signal stopRunning

    RowLayout {

        Button {
            text: "stop"
            onClicked: root.stopRunning()
        }
    }
}
