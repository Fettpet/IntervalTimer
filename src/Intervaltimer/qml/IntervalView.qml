import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

RowLayout {
    id: root
    required property var duration
    required property var description

    TextField {
        id: durationEdit
        validator: IntValidator {
            bottom: 1
        }
        text: root.duration
        onEditingFinished: root.duration = text
    }
    TextField {
        id: descriptionEdit
        text: root.description
        onEditingFinished: root.description = text
        Layout.fillWidth: true
    }
}
