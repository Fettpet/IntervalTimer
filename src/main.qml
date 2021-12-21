import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        Loader {
            id: loader
            sourceComponent: planComponent
            onLoaded: item.planModel = rootPlanModel
        }
        Component {
            id: planComponent
            PlanView {
                childComponent: planComponent
            }
        }
        RowLayout {
            Button {
                text: "Save"
                onClicked: rootPlanModel.savePlanToFile("S:\\test.json")
            }
            Button {
                text: "Load"
                onClicked: rootPlanModel.loadPlanFromFile("S:\\test.json")
            }
        }
    }
}
