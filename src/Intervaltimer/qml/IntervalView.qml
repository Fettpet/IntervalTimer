import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

RowLayout {
    id: root
    required property var duration
    required property var description

    TextField {
        id: descriptionEdit
        selectByMouse: true
        text: root.description
        placeholderText: "Interval description"
        onEditingFinished: root.description = text
        Layout.fillWidth: true

        onFocusChanged: {
            if (focus)
                selectAll()
        }
    }

    TextField {
        id: durationEdit

        selectByMouse: true
        validator: IntValidator {
            bottom: 1
        }
        placeholderText: "Interval duration in seconds"
        text: root.duration
        onEditingFinished: root.duration = text

        onFocusChanged: {
            if (focus)
                selectAll()
        }
    }
}
