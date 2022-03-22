import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Pane {
    id: root

    property QtObject planModel: null
    property color backgroundColor: "#111111"
    property color gradientColor: "#333333"
    property color footerColor: "#333333"
    property color popupColor: "#555555"
    background: Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
    }

    signal startRunning

    Flickable {
        id: main
        anchors.top: parent.top
        anchors.bottom: footerView.top
        anchors.left: parent.left
        anchors.right: parent.right
        contentHeight: loader.implicitHeight
        contentWidth: loader.implicitWidth
        clip: true
        Loader {
            id: loader
            sourceComponent: planComponent
            onLoaded: item.planModel = planModel
        }

        Component {
            id: planComponent
            PlanView {
                backgroundColor: root.backgroundColor
                gradientColor: root.gradientColor
                childComponent: planComponent
            }
        }
    }

    Rectangle {
        id: footerView
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        height: footer.implicitHeight
        anchors.right: parent.right

        color: root.footerColor
        RowLayout {
            id: footer
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Save"
                onClicked: {
                    loaderStorePlan.open()
                    loaderLoadPlan.close()
                }
            }
            Button {
                text: "Load"
                onClicked: {
                    loaderLoadPlan.open()
                    loaderStorePlan.close()
                }
            }
            Button {
                text: "Run"
                onClicked: startRunning()
            }
        }
    }


    StorePlanView {
        id: loaderStorePlan
        backgroundColor: root.popupColor
        anchors.centerIn: parent
    }

    LoadPlanView {
        id: loaderLoadPlan
        backgroundColor: root.popupColor
        anchors.centerIn: parent
    }
}

