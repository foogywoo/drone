TEMPLATE=lib
SOURCES+=contrast0r.c
INCLUDEPATH+=../../

#linux
unix:!macx:TARGET=../../../../../gears/frei0r/contrast0r

#osx
macx:TARGET=../../../../../drone.app/Contents/PlugIns/frei0r/contrast0r
