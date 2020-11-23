import QtQuick 2.5
import QtQuick.Controls 2.5 as QQC2
import QtQuick.Layouts 1.1
import org.kde.kirigami 2.13 as Kirigami

Kirigami.BasicListItem {
    id: delegate

    property bool showArrow: false
    property bool selected: delegate.highlighted || delegate.pressed
    property bool isSearching: false

    topPadding: Kirigami.Units.largeSpacing
    bottomPadding: Kirigami.Units.largeSpacing

    text: model.display
    leading: RowLayout {
        id: row
        Kirigami.Icon {
            source: model.decoration
            Layout.preferredWidth: row.height
            Layout.preferredHeight: row.height
            Layout.leftMargin: (model.DepthRole > 1 && delegate.isSearching) ? ( model.DepthRole - 1 ) * ( row.height * 1.5 ) : 0
        }
    }
    trailing: RowLayout {
        Rectangle {
            id: defaultIndicator
            radius: width * 0.5
            implicitWidth: Kirigami.Units.largeSpacing
            implicitHeight: Kirigami.Units.largeSpacing
            visible: model.showDefaultIndicator && systemsettings.defaultsIndicatorsVisible
            Kirigami.Theme.colorSet: Kirigami.Theme.View
            color: Kirigami.Theme.neutralTextColor
        }

        // Extra space to make the defaults indicators line up vertically for all items
        Item {
            visible: defaultIndicator.visible && !arrow.visible
            implicitWidth: arrow.Layout.preferredWidth
        }

        Kirigami.Icon {
            id: arrow
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: Kirigami.Units.iconSizes.small
            opacity: 0.7
            Layout.preferredWidth: Layout.preferredHeight
            source: (LayoutMirroring.enabled ? "go-next-symbolic-rtl" : "go-next-symbolic")
            visible: delegate.showArrow
            selected: delegate.selected
        }
    }
}
