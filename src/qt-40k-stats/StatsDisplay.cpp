#include "StatsDisplay.hpp"

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>

namespace
{
	/**
		Named after C++20 std::reverse_view

		TODO: Put in another file and complete
	*/
	template <typename Collect>
	struct reverse_view
	{
		using value_type = typename Collect::value_type;
		using iterator = typename Collect::const_reverse_iterator;
		using const_iterator = typename Collect::const_reverse_iterator;

		explicit reverse_view(Collect& collect) :
			collect_{collect}
		{
		}

		const_iterator begin() const
		{
			return collect_.get().rbegin();
		}
		const_iterator end() const
		{
			return collect_.get().rend();
		}

	private:
		std::reference_wrapper<Collect> collect_;
	};
	template <typename Collect>
	reverse_view<Collect> reverse(Collect& collect)
	{
		return reverse_view<Collect>{collect};
	}
	void appendToSet(QtCharts::QBarSet* set, const std::vector<int>& values, bool cumulative)
	{
		int sum = 0;
		for(auto value : reverse(values))
		{
			sum = value + (cumulative ? sum : 0);
			*set << sum;
		}
	}
}

StatsDisplay::StatsDisplay(QObject* parent) :
	QObject(parent),
	title_{"Hit probability"},
	axis_{new QtCharts::QBarCategoryAxis(this)},
	series_{nullptr},
	cumulative_{false}
{
}
const QString& StatsDisplay::title() const
{
	return title_;
}
QtCharts::QBarCategoryAxis* StatsDisplay::axis() const
{
	return axis_;
}
void StatsDisplay::setAxis(QtCharts::QBarCategoryAxis* axis)
{
	if(axis == axis_)
		return;

	if(axis_ && axis_->parent() == this)
		delete axis_;
	axis_ = axis;
	emit axisChanged();
}
QtCharts::QAbstractBarSeries* StatsDisplay::series() const
{
	return series_;
}
void StatsDisplay::setSeries(QtCharts::QAbstractBarSeries* series)
{
	if(series == series_)
		return;

	if(series_ && series_->parent() == this)
		delete series_;
	series_ = series;
	if(series_)
		rebuildSeries();
	emit seriesChanged();
}
bool StatsDisplay::isCumulative() const
{
	return cumulative_;
}
void StatsDisplay::setCumulative(bool cumulative)
{
	if(cumulative == cumulative_)
		return;

	cumulative_ = cumulative;
	rebuildSeries();
	emit cumulativeChanged();
}
void StatsDisplay::rebuildSeries()
{
	std::vector<int> first{50, 25, 20, 5};
	std::vector<int> second{40, 25, 20, 15};

	auto serie1 = new QtCharts::QBarSet("First");
	appendToSet(serie1, first, cumulative_);
	auto serie2 = new QtCharts::QBarSet("Second");
	appendToSet(serie2, second, cumulative_);

	axis_->clear();
	// We have to reverse manually as the setReverse does not work for BarSeries
	for(size_t i = std::max(first.size(), second.size()); i > 0; --i)
	{
		auto text = std::to_string(i -1) + " Hit";
		if(i == 1)
			text += 's';
		axis_->append(QString::fromStdString(text));
	}

	series_->clear();
	series_->append({serie1, serie2});
}