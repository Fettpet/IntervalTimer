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
                loaderStorePlan.open()
            }
        }
        MenuItem {
            text: "Load"
            onTriggered: {
                loaderLoadPlan.open()
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
        id: loaderStorePlan
        backgroundColor: Style.popupColor
        anchors.centerIn: Overlay.overlay
    }

    LoadPlanView {
        id: loaderLoadPlan
        backgroundColor: Style.popupColor
        anchors.centerIn: Overlay.overlay
    }
}
