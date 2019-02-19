#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "StatsDisplay.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("stats", new StatsDisplay());
	engine.load(QUrl(QStringLiteral("qrc:/ui.qml")));

	return app.exec();
}