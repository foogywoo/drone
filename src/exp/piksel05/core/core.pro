######################################################################
# Automatically generated by qmake (1.07a) Sat May 22 15:57:15 2004
######################################################################

include (../../../../config.pro)

message(Drone : Builing Makefile with the following config flags : $$CONFIG)


unix:!macx:QMAKE_CXXFLAGS += -rdynamic

TEMPLATE = lib

INCLUDEPATH += ../../../core/ ../../../core/types/

#mac
macx:INCLUDEPATH += /Developer/Headers/FlatCarbon
macx:LIBS += /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
macx:LIBS += /System/Library/Frameworks/Carbon.framework/Carbon
macx:LIBS += -lz
macx:LIBS += -framework OpenGL -framework CoreAudio -framework CoreMidi
macx:QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@executable_path/../Frameworks/
macx:TARGET = ../../../../drone.app/Contents/Frameworks/droneTACore
macx:QMAKE_CXXFLAGS += -D__MACOSX_CORE__

#linux
unix:!macx:LIBS += -L/usr/X11R6/lib -lGL -lasound -lpthread
unix:!macx:TARGET = ../../../../lib/droneTACore
unix:!macx:QMAKE_CXXFLAGS += -D__LINUX_ALSASEQ__

HEADERS += SimpleGraph.h \
TA_CityGraph.h \
TA_DataType.h
SOURCES += TA_CityGraph.cpp \
TA_DataType.cpp