import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Plan {
        plan: rootPlan
    }

}
