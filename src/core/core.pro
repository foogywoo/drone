######################################################################
# Automatically generated by qmake (1.07a) Sat May 22 15:57:15 2004
######################################################################

CONFIG = qt warn_on thread 
include (../../flags.pro)

unix:!macx:QMAKE_CXXFLAGS += -rdynamic
# Use gprof
gprof {
  QMAKE_CXXFLAGS+=-pg
}

# Debug settings
debug {
  OBJECTS_DIR = debug
  #QMAKE_CXXFLAGS +=-DDEBUG_LEVEL=0
  QMAKE_CXXFLAGS +=-DDEBUG_LEVEL=2 -DSINGLE_THREADED_PLAYBACK
}

# Optimized settings
release {
  OBJECTS_DIR = release  
  QMAKE_CXXFLAGS_RELEASE -= -O2 -Os
  
  unix:!macx:QMAKE_CXXFLAGS += -DDEBUG_LEVEL=-1 -funroll-loops -fomit-frame-pointer -pipe -O3
  macx:QMAKE_CXXFLAGS += -DDEBUG_LEVEL=-1 -funroll-loops -Os
  
  p4 {
    QMAKE_CXXFLAGS += -march=pentium4
  }
  p3 {
    QMAKE_CXXFLAGS += -march=pentium3
  }
  athlon {
    QMAKE_CXXFLAGS += -march=athlon    
  }

  G5 {
	QMAKE_CXXFLAGS += -DDEBUG_LEVEL=-1 -fast
  }
  
}


TEMPLATE = lib
INCLUDEPATH += . types contrib/frei0r

#mac
macx:INCLUDEPATH += /Developer/Headers/FlatCarbon
macx:LIBS += /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
macx:LIBS += /System/Library/Frameworks/Carbon.framework/Carbon
macx:LIBS += -lz
macx:LIBS += -framework OpenGL -framework CoreMidi
macx:QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@executable_path/../Frameworks/
macx:TARGET = ../../drone.app/Contents/Frameworks/droneCore
macx:QMAKE_CXXFLAGS += -D__MACOSX_CORE__

#linux
unix:!macx:LIBS += -L/usr/X11R6/lib -lGL -lasound -lpthread
unix:!macx:TARGET = ../../lib/droneCore
unix:!macx:QMAKE_CXXFLAGS += -D__LINUX_ALSASEQ__


HEADERS += config.h \
error.h \
Array.h \
Array2D.h \
CircularBuffer.h \
ColorSpace.h \
ConnectionItem.h \
Engine.h \
Gear.h \
types/AbstractType.h \
types/AreaArrayType.h \
types/FFTType.h \
types/ValueType.h \
types/VideoRGBAType.h \
types/SignalType.h \
types/DisplaceGrid.h \
types/ArrayType.h \
types/Array2DType.h \
types/VideoChannelType.h \
types/VideoBinaryType.h \
types/PaletteRGBAType.h \
types/EnumType.h \
GearClassification.h \
GearGui.h \
GearConverter.h \
GearMaker.h \
Math.h \
MetaGear.h \
AbstractPlug.h \
Plug.h \
PlugBox.h \
Properties.h \
Project.h \
Rasterer.h \
SummedAreaTable.h \
Schema.h \
SchemaGui.h \
SignalInfo.h \
ThreadUtil.h \
Timing.h \
Typedefs.h \
Utils.h \
VideoInfo.h \
XMLHelper.h \
RtMidi/RtMidi.h \
RtMidi/RtError.h

SOURCES += error.cpp \
ConnectionItem.cpp \
Engine.cpp \
Gear.cpp \
types/VideoRGBAType.cpp \
GearGui.cpp \
GearMaker.cpp \
MetaGear.cpp \
AbstractPlug.cpp \
PlugBox.cpp \
Properties.cpp \
Project.cpp \
Rasterer.cpp \
Schema.cpp \
SchemaGui.cpp \
SignalInfo.cpp \
Timing.cpp \
VideoInfo.cpp \
XMLHelper.cpp  \
RtMidi/RtMidi.cpp


