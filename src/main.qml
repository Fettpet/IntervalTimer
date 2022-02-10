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

    Loader {
        id: editorLoader
        active: !root.isRunning
        width: !root.isRunning ? parent.width : 0
        height: !root.isRunning ? parent.height : 0
        sourceComponent: PlanEditorView {
            planModel: PlanModel
            width: root.width
            height: root.height
            onStartRunning: {
                PlanRunner.start()
                root.isRunning = true
            }
        }
    }
    Loader {
        id: runnerLoader
        active: root.isRunning
        width: root.isRunning ? parent.width : 0
        height: root.isRunning ? parent.height : 0
        sourceComponent: PlanRunningView {
            width: root.width
            height: root.height
            onStopRunning: {
                root.isRunning = false
            }
        }
    }
}
