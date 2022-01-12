import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root
    property QtObject planModel: null

    signal startRunning
    ColumnLayout {
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
            Button {
                text: "Save"
                onClicked: root.planModel.savePlanToFile("S:\\test.json")
            }
            Button {
                text: "Load"
                onClicked: root.planModel.loadPlanFromFile("S:\\test.json")
            }
            Button {
                text: "run"
                onClicked: startRunning()
            }
        }
    }
}
