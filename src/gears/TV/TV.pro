TEMPLATE=lib
SOURCES+=Gear_TV.cpp GearGui_TV.cpp
HEADERS+=Gear_TV.h GearGui_TV.h
INCLUDEPATH+=../../core/ ../../core/types

#linux
linux:LIBS+=-L../../../lib/ -ldroneCore
linux:TARGET=../../../gears/Gear_TV

#osx
mac:TARGET=../../../drone.app/Contents/PlugIns/Gear_TV
mac:LIBS+=-L../../../drone.app/Contents/Frameworks -ldroneCore


