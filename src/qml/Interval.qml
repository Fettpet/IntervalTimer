import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0


RowLayout {
    id: root
    required property var model

    TextField {
        id: duration
        text: model.duration
        onEditingFinished: model.duration = text;
    }
    TextField {
        id: description
        text: model.description
        onEditingFinished: model.description = text;
        Layout.fillWidth: true
    }
}
