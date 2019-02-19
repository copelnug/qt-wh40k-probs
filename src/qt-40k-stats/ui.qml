import QtCharts 2.2
import QtQuick 2.6
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.11
import QtQuick.Window 2.2

ApplicationWindow {
	title: "Wh40k Probability Distribution"
	visible: true
	visibility: Window.Maximized

	ColumnLayout {
		anchors.fill: parent
		spacing: 2
		
		RowLayout {
			Label { text: "Cumulative:" }
			Switch {
				checked: stats.cumulative
				onClicked: stats.cumulative = checked 
			}
		}
		ChartView {
			title:  stats.title
			Layout.fillWidth: true
			Layout.fillHeight: true
			legend.alignment: Qt.AlignLeft
			antialiasing: true

			HorizontalBarSeries {
				id: series

				axisX: ValueAxis {
					min: 0
					max: 100
				}

				axisY: stats.axis
				Component.onCompleted: stats.series = series
			}
		}
	}
}