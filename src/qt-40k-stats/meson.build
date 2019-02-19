
qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Qml', 'Gui', 'Charts'])

qtfiles = qt5.preprocess(
	moc_headers: 'StatsDisplay.hpp',
	qresources: 'ui.qrc'
)

qml = configure_file(
	copy: true,
	input: 'ui.qml',
	output: '@PLAINNAME@'
)

executable('qt-40k-stats',
	'main.cpp',
	'StatsDisplay.cpp',
	qtfiles,
	dependencies: qt5_dep
)