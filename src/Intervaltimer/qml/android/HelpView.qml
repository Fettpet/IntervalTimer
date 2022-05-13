import QtQuick
import QtQuick.Controls

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    TextArea {
        readOnly: true
        text: "Mit dem IntervalTimer können Trainingsintervale verschachtelt werden. \n \
Ein Plan besteht aus Plänen und Intervalen. Der Plan hat einen Namen \n \
und einen Wiederholungszähler. Ein Interval besteht aus einem Namen und \n \
einer Dauer. \n \n \
Ein Plan wird von oben nach unten ausgeführt. Abhängig vom Wiederholungs- \n \
zähler wird er danach wiederholt."
    }
}
