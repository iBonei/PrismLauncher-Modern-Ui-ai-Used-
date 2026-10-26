import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: shell
    color: "#090f19"
    property string selectedId: prism.qmlSelectedId
    property var cards: prism.qmlInstances
    property string query: ""
    property var visibleCards: cards.filter(function(card) {
        return !query || card.name.toLowerCase().indexOf(query.toLowerCase()) >= 0
               || card.version.toLowerCase().indexOf(query.toLowerCase()) >= 0
    })
    property var activeCard: {
        for (var i = 0; i < cards.length; ++i)
            if (cards[i].id === selectedId) return cards[i]
        return null
    }

    function action(name) { prism.qmlAction(name) }

    Rectangle {
        id: rail
        width: 224
        color: "#101a2a"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Rectangle { width: 1; anchors.right: parent.right; height: parent.height; color: "#243347" }

        Rectangle {
            x: 20; y: 24; width: 39; height: 39; radius: 12; color: "#29485e"
            Text { anchors.centerIn: parent; text: "◈"; color: "#8ee6ec"; font.pixelSize: 29; font.bold: true }
        }
        Text { x: 69; y: 25; text: "PRISM"; color: "#f5fbff"; font.pixelSize: 19; font.bold: true; font.letterSpacing: 1.4 }
        Text { x: 69; y: 49; text: "REIMAGINED"; color: "#65b9c9"; font.pixelSize: 10; font.letterSpacing: 1.3 }

        Text { x: 23; y: 112; text: "WORKSPACE"; color: "#687e94"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1.6 }
        Repeater {
            model: [
                { label: "Library", glyph: "▦", task: "library" },
                { label: "Create instance", glyph: "＋", task: "new" },
                { label: "Accounts", glyph: "♙", task: "accounts" },
                { label: "Settings", glyph: "⚙", task: "settings" }
            ]
            delegate: Rectangle {
                required property var modelData
                required property int index
                x: 12; y: 138 + index * 57; width: rail.width - 24; height: 47; radius: 12
                color: modelData.task === "library" ? "#203a4c" : hover.containsMouse ? "#1c2d40" : "transparent"
                border.color: modelData.task === "library" ? "#3d6f88" : "transparent"
                Text { x: 17; anchors.verticalCenter: parent.verticalCenter; text: modelData.glyph; color: "#a4dbe6"; font.pixelSize: 20 }
                Text { x: 51; anchors.verticalCenter: parent.verticalCenter; text: modelData.label; color: "#ebf4fb"; font.pixelSize: 13; font.bold: modelData.task === "library" }
                MouseArea { id: hover; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: shell.action(modelData.task) }
            }
        }

        Rectangle {
            x: 16; width: rail.width - 32; height: 100; radius: 13
            anchors.bottom: parent.bottom; anchors.bottomMargin: 20
            color: "#172538"; border.color: "#283f54"
            Text { x: 15; y: 14; text: "YOUR WORKSPACE"; color: "#64c6d8"; font.pixelSize: 10; font.bold: true }
            Text { x: 15; y: 37; text: cards.length + (cards.length === 1 ? " instance" : " instances"); color: "#f2f8fd"; font.pixelSize: 17; font.bold: true }
            Text { x: 15; y: 69; text: "Built around your worlds"; color: "#8298ad"; font.pixelSize: 11 }
        }
    }

    Item {
        id: workspace
        anchors.left: rail.right
        anchors.right: inspector.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Rectangle {
            id: toolbar
            x: 29; y: 26; width: parent.width - 58; height: 58; color: "transparent"
            Text { x: 0; y: 0; text: "My library"; color: "#f6faff"; font.pixelSize: 29; font.bold: true }
            Text { x: 1; y: 39; text: "Your Minecraft instances, all in one place"; color: "#859bb0"; font.pixelSize: 12 }
            Rectangle {
                id: create
                width: 166; height: 42; radius: 11; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                color: createHover.containsMouse ? "#67dbd4" : "#45c7ca"
                Text { anchors.centerIn: parent; text: "+  New instance"; color: "#061920"; font.pixelSize: 13; font.bold: true }
                MouseArea { id: createHover; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: shell.action("new") }
            }
        }

        Flickable {
            id: feed
            anchors.left: parent.left; anchors.right: parent.right
            anchors.top: toolbar.bottom; anchors.bottom: parent.bottom
            topMargin: 0; clip: true
            contentHeight: stack.implicitHeight + 48
            ScrollBar { }
            Column {
                id: stack
                x: 29; width: feed.width - 58; spacing: 26

                Rectangle {
                    width: parent.width; height: 214; radius: 18
                    color: "#152c3d"; border.color: "#2d5368"
                    Rectangle {
                        width: parent.width * 0.4; height: parent.height
                        anchors.right: parent.right; color: "#1b3949"; radius: 18
                        opacity: 0.55
                    }
                    Rectangle {
                        x: parent.width - 177; y: 44; width: 104; height: 104; radius: 24
                        rotation: -12; color: "#2d5664"; border.color: "#46798a"; border.width: 2
                        Text { anchors.centerIn: parent; text: "◈"; font.pixelSize: 75; color: "#78d3d8" }
                    }
                    Text { x: 27; y: 25; text: "YOUR NEXT ADVENTURE"; color: "#62c6cf"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1.5 }
                    Text { x: 27; y: 54; text: activeCard ? activeCard.name : "Build something great"; color: "#f4fbff"; font.pixelSize: 28; font.bold: true; width: parent.width - 220; elide: Text.ElideRight }
                    Text { x: 29; y: 100; text: activeCard ? activeCard.version + "  •  " + activeCard.status : "Create a new profile or select one from your library."; color: "#afc7d5"; font.pixelSize: 12 }
                    Rectangle {
                        x: 27; y: 148; width: 153; height: 42; radius: 10
                        color: activeCard ? "#54ce9a" : "#2f6980"
                        Text { anchors.centerIn: parent; text: activeCard ? "▶   Play now" : "+   Create profile"; color: "#092220"; font.pixelSize: 13; font.bold: true }
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: shell.action(activeCard ? "launch" : "new") }
                    }
                }

                Row {
                    width: parent.width; height: 41; spacing: 12
                    Text { text: "Installed profiles"; color: "#f1f7fd"; font.pixelSize: 20; font.bold: true; anchors.verticalCenter: parent.verticalCenter }
                    Text { text: "(" + visibleCards.length + ")"; color: "#7b9bae"; font.pixelSize: 14; anchors.verticalCenter: parent.verticalCenter }
                    Item { width: Math.max(8, parent.width - 560); height: 1 }
                    Rectangle {
                        width: 260; height: 39; radius: 10; color: "#142335"; border.color: "#2a4358"
                        Text { x: 14; anchors.verticalCenter: parent.verticalCenter; visible: search.text.length === 0; text: "Search your profiles..."; color: "#70889e"; font.pixelSize: 12 }
                        TextInput { id: search; anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 10; verticalAlignment: TextInput.AlignVCenter; color: "#f0f7ff"; font.pixelSize: 12; selectionColor: "#367e94"; onTextChanged: shell.query = text }
                    }
                }

                Grid {
                    id: cardGrid
                    width: parent.width
                    spacing: 16
                    columns: Math.max(1, Math.floor((width + spacing) / 273))
                    Repeater {
                        model: visibleCards
                        delegate: Rectangle {
                            required property var modelData
                            id: cardTile
                            width: Math.min(257, (cardGrid.width - (cardGrid.columns - 1) * cardGrid.spacing) / cardGrid.columns)
                            height: 210; radius: 15
                            color: selectedId === modelData.id ? "#1e3d50" : over.containsMouse ? "#192f41" : "#152537"
                            border.color: selectedId === modelData.id ? "#60d2e7" : over.containsMouse ? "#4a7185" : "#294154"
                            border.width: selectedId === modelData.id ? 2 : 1
                            Rectangle {
                                x: 12; y: 12; width: parent.width - 24; height: 111; radius: 11
                                color: "#1b3946"
                                Rectangle { anchors.fill: parent; radius: 11; color: "#29505a"; opacity: 0.38 }
                                Image {
                                    anchors.centerIn: parent; width: 72; height: 72
                                    source: "image://prismicons/" + encodeURIComponent(modelData.iconKey)
                                    fillMode: Image.PreserveAspectFit; smooth: false
                                }
                            }
                            Text { x: 16; y: 134; width: parent.width - 32; text: modelData.name; font.pixelSize: 15; font.bold: true; color: "#f3f9fd"; elide: Text.ElideRight }
                            Text { x: 16; y: 160; width: parent.width - 32; text: modelData.version; font.pixelSize: 11; color: "#9cb4c9"; elide: Text.ElideRight }
                            Rectangle { x: 16; y: 190; width: 6; height: 6; radius: 3; color: modelData.running ? "#4bddaa" : "#53beda" }
                            Text { x: 29; y: 184; width: parent.width - 42; text: modelData.running ? "Running" : "Ready"; color: "#89aabf"; font.pixelSize: 11 }
                            MouseArea { id: over; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: prism.qmlSelectInstance(modelData.id); onDoubleClicked: { prism.qmlSelectInstance(modelData.id); shell.action("launch") } }
                        }
                    }
                }
                Text { visible: visibleCards.length === 0; text: query ? "No profiles match your search." : "No instances yet. Create one to get started."; color: "#8da4b7"; font.pixelSize: 15 }
            }
        }
    }

    Rectangle {
        id: inspector
        width: Math.min(346, Math.max(285, shell.width * 0.24))
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom
        color: "#101b2b"
        Rectangle { width: 1; height: parent.height; color: "#273a50" }
        Text { x: 24; y: 33; text: "INSTANCE DETAILS"; color: "#6fc7d7"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1.5 }
        Rectangle {
            x: 24; y: 69; width: parent.width - 48; height: 188; radius: 15
            color: "#1a3043"; border.color: "#33556a"
            Image { anchors.centerIn: parent; width: 112; height: 112; visible: activeCard !== null; source: activeCard ? "image://prismicons/" + encodeURIComponent(activeCard.iconKey) : ""; fillMode: Image.PreserveAspectFit; smooth: false }
            Text { anchors.centerIn: parent; visible: activeCard === null; text: "◈"; color: "#36586b"; font.pixelSize: 90 }
        }
        Text { x: 24; y: 281; width: parent.width - 48; text: activeCard ? activeCard.name : "Select a profile"; color: "#f2f8ff"; font.pixelSize: 23; font.bold: true; elide: Text.ElideRight }
        Text { x: 24; y: 319; width: parent.width - 48; text: activeCard ? activeCard.version : "Your instance details appear here."; color: "#8faabd"; font.pixelSize: 12 }
        Rectangle { x: 24; y: 367; width: parent.width - 48; height: 1; color: "#2b4054" }

        Repeater {
            model: [
                { name: "Launch Minecraft", id: "launch", tint: "#4dd19a" },
                { name: "Manage mods", id: "mods", tint: "#20394d" },
                { name: "Manage worlds", id: "worlds", tint: "#20394d" },
                { name: "Instance settings", id: "edit", tint: "#20394d" },
                { name: "Open instance folder", id: "folder", tint: "#20394d" }
            ]
            delegate: Rectangle {
                required property var modelData
                required property int index
                x: 24; y: 391 + index * 57; width: inspector.width - 48; height: 45; radius: 10
                color: activeCard === null ? "#192b38" : modelData.id === "launch" ? "#4dd19a" : mouse.containsMouse ? "#2a4b61" : "#20394d"
                border.color: activeCard === null ? "#213546" : modelData.id === "launch" ? "#6de9b2" : "#36536b"
                Text { x: 17; anchors.verticalCenter: parent.verticalCenter; text: modelData.name; color: activeCard && modelData.id === "launch" ? "#08261d" : "#d8e8f5"; font.pixelSize: 13; font.bold: modelData.id === "launch" }
                Text { anchors.right: parent.right; anchors.rightMargin: 15; anchors.verticalCenter: parent.verticalCenter; text: "›"; font.pixelSize: 23; color: activeCard && modelData.id === "launch" ? "#08261d" : "#7897a9" }
                MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; enabled: activeCard !== null; cursorShape: Qt.PointingHandCursor; onClicked: shell.action(modelData.id) }
            }
        }
    }
}
