import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import interval 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Frame {
        ListView {
            implicitWidth: 250
            implicitHeight: 250
            clip: true

            model: PlanModel {
                plan: rootPlan
            }

            delegate: RowLayout {
                TextField {
                    text: model.duration
                    onEditingFinished: {
                        console.error(text);
                        model.duration = text;
                    }
                }
                TextField {
                    text: model.description
                    onEditingFinished: {
                        console.error(text);
                        model.description = text;
                    }
                    Layout.fillWidth: true
                }
            }
        }
    }
}
