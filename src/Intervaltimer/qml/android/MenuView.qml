import QtQuick
import QtQuick.Controls

import Intervaltimer
import Intervaltimer.Android

ToolButton {
    id: myButton
    background: Rectangle {
        color: "white"
        anchors.fill: parent
    }

    icon {

        color: "red"
        source: "qrc:/IntervalApplication/ressources/image/menu.png"
    }
    onClicked: myMenu.open()
    Menu {
        id: myMenu
        MenuItem {
            text: "Save"
            onTriggered: {
                storePlan.open()
            }
        }
        MenuItem {
            text: "Load"
            onTriggered: {
                loadPlan.open()
            }
        }
        MenuSeparator {}
        MenuItem {
            text: "About"
        }
        MenuItem {
            text: "Licences"
            onTriggered: {
                licence.open()
            }
        }
        MenuItem {
            text: "Help"
        }
        MenuItem {
            text: "Copyright"
        }
    }

    LicenceView {
        id: licence
        // backgroundColor: Style.popupColor
        anchors.centerIn: Overlay.overlay
    }

    StorePlanView {
        id: storePlan
        backgroundColor: Style.popupColor
        anchors.centerIn: Overlay.overlay
    }

    LoadPlanView {
        id: loadPlan
        backgroundColor: Style.popupColor
        anchors.centerIn: Overlay.overlay
    }
}
