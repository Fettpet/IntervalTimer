import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Window {
    id: root
    property bool isRunning: false

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        id: layout

        Loader {
            id: editorLoader
            active: !root.isRunning
            sourceComponent: PlanEditorView {
                planModel: PlanModel
                onStartRunning: {
                    PlanRunner.start()
                    root.isRunning = true
                }
            }
        }
        Loader {
            id: runnerLoader
            active: root.isRunning
            sourceComponent: PlanRunningView {
                onStopRunning: {
                    root.isRunning = false
                }
            }
        }
    }
}
