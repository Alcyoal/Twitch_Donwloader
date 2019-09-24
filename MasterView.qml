import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5


Page{
    visible: true
    title: qsTr("Hello World")
    Rectangle
    {
        anchors.fill: parent
        color: "grey"
        Rectangle
        {
            height: parent.height / 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            color: Qt.darker(parent.color)
            MouseArea
            {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.OpenHandCursor
                onPressed:
                {
                    cursorShape = Qt.ClosedHandCursor
                    ui_hostWindow.setClicked(true)
                }
                onReleased:
                {
                    cursorShape = Qt.OpenHandCursor
                    ui_hostWindow.setClicked(false)
                }
            }
        }
        Rectangle
        {
            width: 100
            height: 100
            anchors.centerIn: parent
            color: "blue"
            MouseArea
            {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: ui_injectedSignaler.buttonPressed();
            }
        }

        Rectangle
        {
            id: zoneInput
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: parent.width / 10
            anchors.rightMargin: parent.width / 10
            anchors.bottom: parent.bottom
            height: parent.height / 5
            color: "transparent"
            Rectangle{
                id: input1Rectangle
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: zoneInput.top
                height: zoneInput.height / 5
                anchors.margins: 5
                color: "white"
                TextInput
                {
                    id: input1
                    anchors.fill: parent
                    validator: IntValidator{}
                    color: "black"
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    selectByMouse: true
                    onTextChanged: ui_injectedSignaler.setInput1(text);
                }
            }
            Rectangle{
                id: input2Rectangle
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: input1Rectangle.bottom
                height: zoneInput.height / 5
                anchors.margins: 5
                color: "white"
                TextInput
                {
                    id: input2
                    anchors.fill: parent
                    validator: IntValidator{}
                    color: "black"
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    selectByMouse: true
                    onTextChanged: ui_injectedSignaler.setInput2(text);
                }
            }
            Rectangle{
                id: input3Rectangle
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: input2Rectangle.bottom
                height: zoneInput.height / 5
                anchors.margins: 5
                color: "white"
                TextInput
                {
                    id: input3
                    anchors.fill: parent
                    validator: IntValidator{}
                    color: "black"
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    selectByMouse: true
                    onTextChanged: ui_injectedSignaler.setInput3(text);
                }
            }
            Rectangle
            {
                anchors.right: parent.right
                anchors.top: input3Rectangle.bottom
                height: zoneInput.height / 5
                width: parent.width / 2
                anchors.margins: 5
                color: "red"
                Text {
                    anchors.fill: parent
                    text: qsTr("Validate input")
                }
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: ui_injectedSignaler.validateInput();
                }
            }
        }
    }
}
