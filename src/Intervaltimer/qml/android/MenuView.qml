import QtQuick
import QtQuick.Controls

import Intervaltimer
import Intervaltimer.Android

ToolButton {
    id: myButton

    icon {
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
            onTriggered: {
                about.open()
            }
        }
        MenuItem {
            text: "Licences"
            onTriggered: {
                licence.open()
            }
        }
        MenuItem {
            text: "Help"
            onTriggered: {
                help.open()
            }
        }
        MenuItem {
            text: "Copyright"
            onTriggered: {
                copyright.open()
            }
        }
    }

    LicenceView {
        id: licence
        anchors.centerIn: Overlay.overlay
    }

    AboutView {
        id: about
        anchors.centerIn: Overlay.overlay
    }

    CopyrightView {
        id: copyright
        anchors.centerIn: Overlay.overlay
    }

    HelpView {
        id: help
        anchors.centerIn: Overlay.overlay
    }

    StorePlanView {
        id: storePlan
        backgroundColor: Style.popupColor
        anchors.centerIn: Overlay.overlay
    }

    LoadPlanView {
        id: loadPlan
        anchors.centerIn: Overlay.overlay
    }
}
