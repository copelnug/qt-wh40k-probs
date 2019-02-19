#ifndef QT_40K_STATS_STATS_DISPLAY_HPP_INCLUDED
#define QT_40K_STATS_STATS_DISPLAY_HPP_INCLUDED
#include <QObject>
#include <QString>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <string>
#include <vector>


class StatsDisplay : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString title READ title NOTIFY titleChanged)
	Q_PROPERTY(QtCharts::QBarCategoryAxis* axis READ axis WRITE setAxis NOTIFY axisChanged)
	Q_PROPERTY(QtCharts::QAbstractBarSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
	Q_PROPERTY(bool cumulative READ isCumulative WRITE setCumulative NOTIFY cumulativeChanged)

public:
	explicit StatsDisplay(QObject* parent = nullptr);

	const QString& title() const;

	QtCharts::QBarCategoryAxis* axis() const;
	void setAxis(QtCharts::QBarCategoryAxis* axis);

	QtCharts::QAbstractBarSeries* series() const;
	void setSeries(QtCharts::QAbstractBarSeries* series);

	bool isCumulative() const;


public slots:
	void setCumulative(bool cumulative);

signals:
	void titleChanged();
	void axisChanged();
	void seriesChanged();
	void cumulativeChanged();
private:
	void rebuildSeries();

	QString title_;
	QtCharts::QBarCategoryAxis* axis_;
	QtCharts::QAbstractBarSeries* series_;
	bool cumulative_;
};

#endif