import QtQuick
import QtQuick.Window

Window {
    visible: true
    color: "transparent"
    title: "ScreenCapture"

    Image {
        id: backgroundImage
        source: "image://ProviderImgScreen/background"
        anchors.fill: parent
    }
    MouseArea {
        anchors.fill: parent
        onPressed: mouse => {
            console.log("allen");
        }
    }
}
