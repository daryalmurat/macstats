import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0

Window {
    visible: true
    width: 400
    height: 320
    minimumWidth: 400
    minimumHeight: 320
    maximumWidth: 400
    maximumHeight: 320
    flags: Qt.Dialog | Qt.MSWindowsFixedSizeDialogHint
    color: "#333333"
    title: qsTr("MAC STATS")


    ListView {
        clip: true
        anchors.fill: parent
        model: metricdatamodel
        //take as much width as possible with a binding
        width: parent.width



        delegate: ColumnLayout {
            width: parent.width
            RowLayout {


                TextField {

                    color: "#fff"
                    background: Item {}
                    // render data from model
                    text: name
                    Layout.fillWidth: true
                    Layout.minimumWidth: 270
                    Layout.preferredWidth: 270
                    Layout.maximumWidth: 270


                }

                TextField {

                    color: "#fff"
                    background: Item {}
                    // render data from model
                    text: value
                    Layout.minimumWidth: 150
                    Layout.preferredWidth: 150
                    Layout.maximumWidth: 150
                }

            }
            Rectangle { color: "#666"; height: 1; Layout.fillWidth: true }
        }

    }
}
