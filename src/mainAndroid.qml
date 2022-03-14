import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("IntervalTimer")
    property bool isRunning: false

    color: "teal"

    Text {
        text: "Hello World"
    }
}
