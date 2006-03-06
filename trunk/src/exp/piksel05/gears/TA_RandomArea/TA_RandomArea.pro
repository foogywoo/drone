include (../../../../../config.pro)

TEMPLATE=lib

SOURCES+=Gear_TA_RandomArea.cpp
HEADERS+=Gear_TA_RandomArea.h

INCLUDEPATH+=../../../../core/ ../../core/ ../../../../core/types
unix:!macx:LIBS+=-L../../../../../lib/ -ldroneCore -ldroneTACore
unix:!macx:TARGET=../../../../../gears/Gear_TA_RandomArea
unix:!macx:QMAKE_RPATH = -Wl,-rpath,lib/,-rpath,

#osx
macx:LIBS+=-L../../../../../drone.app/Contents/Frameworks -ldroneCore -ldroneTACore
macx:TARGET=../../../../../drone.app/Contents/PlugIns/Gear_TA_RandomArea
macx:QMAKE_LFLAGS+=-read_only_relocs suppress
