import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

        Button {
            text: "Register"
            anchors.left: parent.left
            onClicked: CarRentalController.registerNewItem();
            //onClicked: cppNumber.decrement()
        }
        Button {
            text: "Increment"
            anchors.right: parent.right
            onClicked: cppNumber.increment()
        }

        Button {
            id: resultButton
            text: cppNumber.getNumber()
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Connections {
            target: cppNumber
            onNumberChanged: {
                resultButton.text = cppNumber.getNumber();
            }
        }

}
