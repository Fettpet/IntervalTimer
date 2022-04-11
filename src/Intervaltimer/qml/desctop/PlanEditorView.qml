import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Desctop

Frame {
    id: root
    property QtObject planModel: null

    background: Rectangle {
        width: root.width
        height: root.height
        color: "teal"
    }

    signal startRunning
    ColumnLayout {
        id: layout
        Loader {
            sourceComponent: planComponent
            onLoaded: item.planModel = planModel
        }

        Component {
            id: planComponent
            PlanView {
                childComponent: planComponent
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
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

        StorePlanView {
            id: loaderStorePlan
            anchors.centerIn: layout
        }

        LoadPlanView {
            id: loaderLoadPlan
            anchors.centerIn: layout
        }
    }
}
