######################################################################
# Automatically generated by qmake (1.07a) Sat May 22 15:57:15 2004
######################################################################

include (config.pro)

QMAKE_CXXFLAGS += -rdynamic
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
  QMAKE_CXXFLAGS +=-DDEBUG_LEVEL=-1 -funroll-loops -fomit-frame-pointer -pipe
  p4 {
    QMAKE_CXXFLAGS += -march=pentium4
  }
  athlon {
    QMAKE_CXXFLAGS += -march=athlon    
  }

  ppc {
    QMAKE_CXXFLAGS += -march=ppc
  }
  
}


TEMPLATE = lib
INCLUDEPATH += . types contrib/frei0r
LIBS += -lGLU -lGL
TARGET = ../../lib/droneCore

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
GearGui.h \
GearConverter.h \
GearMaker.h \
Math.h \
MetaGear.h \
AbstractPlug.h \
Plug.h \
PlugBox.h \
Properties.h \
Rasterer.h \
SummedAreaTable.h \
Schema.h \
SchemaGui.h \
SignalInfo.h \
ThreadUtil.h \
Timing.h \
Typedefs.h \
Utils.h \
VideoInfo.h

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
Rasterer.cpp \
Schema.cpp \
SchemaGui.cpp \
SignalInfo.cpp \
Timing.cpp \
VideoInfo.cpp


