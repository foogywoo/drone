######################################################################
# Automatically generated by qmake (1.07a) Sat May 22 15:57:15 2004
######################################################################

TEMPLATE = app
DEPENDPATH += src
INCLUDEPATH += . src src/gears src/types /usr/include/libmpeg3
LIBS += -lsndfile -lfftw3 -lXxf86vm -lmpeg3 -lGLU -lportaudio -lGL -lXv
CONFIG += thread debug

HEADERS += config.h \
#           src/CircularBufferSignal.h \
           src/ColorSpace.h \
           src/ConnectionItem.h \
           src/Engine.h \
#           src/FrequencyAnalyzer.h \
           src/Gear.h \
	    src/types/AbstractType.h \
	    src/types/VideoType.h \
	    src/types/SignalType.h \
	    src/types/MatrixType.h \
#           src/gears/Gear_AudioInput.h \
#           src/gears/Gear_AudioOutput.h \
#           src/gears/Gear_AudioSource.h \
#           src/gears/Gear_AverageSignal.h \
#           src/gears/Gear_Blur.h \
#           src/gears/Gear_ColorAdjust.h \
#           src/gears/Gear_Contrast.h \
#     	    src/gears/Gear_ColorQuantize.h \
#           src/gears/Gear_ColorQuantizeWu.h \
#           src/gears/Gear_ClusteredDither.h \
#           src/gears/Gear_DataOut.h \
#           src/gears/Gear_DiffDist.h \
#           src/gears/Gear_Edge.h \
#           src/gears/Gear_Enveloppe.h \
#           src/gears/Gear_FilterSignal.h \
#           src/gears/Gear_FreqBoxes.h \
#           src/gears/Gear_Gain.h \
           src/gears/Gear_GrayScale.h \
#           src/gears/Gear_HalfToning.h \
#           src/gears/Gear_Image.h \
#           src/gears/Gear_KDTree.h \
#           src/gears/Gear_MasterFrequency.h \
#           src/gears/Gear_MedianFilter.h \
#           src/gears/Gear_NGone.h \
#           src/gears/Gear_Osc.h \
#           src/gears/Gear_Oscilloscope.h \
#           src/gears/Gear_PatternGen.h \
#           src/gears/Gear_Saturation.h \
#           src/gears/Gear_SimpleDelay.h \
#           src/gears/Gear_Slider.h \
#           src/gears/Gear_TV.h \
#           src/gears/Gear_VideoAdd.h \
#           src/gears/Gear_VideoBlend.h \
           src/gears/Gear_VideoInput.h \
#           src/gears/Gear_VideoMix.h \
           src/gears/Gear_VideoOutput.h \
          src/gears/Gear_VideoSource.h \
           src/GearGui.h \
#           src/GearGui_Slider.h \
#           src/GearGui_TV.h \
           src/GearMaker.h \
           src/GearPropertiesDialog.h \
           src/MainWindow.h \
           src/Math.h \
	   src/AbstractPlug.h \
           src/Plug.h \
           src/PlugBox.h \
#           src/PlugSignal.h \
#           src/PlugSignalIn.h \
#           src/PlugSignalOut.h \
#           src/PlugVideo.h \
#           src/PlugVideoCompose.h \
#           src/PlugVideoComposeIn.h \
#           src/PlugVideoComposeOut.h \
#           src/PlugVideoIn.h \
#           src/PlugVideoOut.h \
           src/Properties.h \
           src/PropertyControl.h \
           src/PropertyControlFilename.h \
           src/PropertyControlString.h \
	   src/PropertyControlBool.h \
#           src/Rasterer.h \
           src/SummedAreaTable.h \
           src/SchemaEditor.h \
           src/Signal.h \
#           src/SignalCircularBuffer.h \
           src/SignalInfo.h \
           src/Timing.h \
           src/Typedefs.h \
           src/VideoInfo.h \	   
	   src/VideoOutput.h \
	   src/VideoOutputMaker.h \
	   src/VideoOutputX11Base.h \
	   src/VideoOutputXv.h \
	   src/VideoOutputShm.h \
	   src/VideoOutputGl.h \
	   src/Play.xpm \
	   src/Pause.xpm \
	   src/splash.xpm \
	   COPYING	   
SOURCES +=     src/ConnectionItem.cpp \
#           src/CircularBufferSignal.cpp \
           src/drone.cpp \
           src/Engine.cpp \
#           src/FrequencyAnalyzer.cpp \
           src/Gear.cpp \
	    src/types/MatrixType.cpp \
#           src/gears/Gear_AudioInput.cpp \
#           src/gears/Gear_AudioOutput.cpp \
#           src/gears/Gear_AudioSource.cpp \
#           src/gears/Gear_AverageSignal.cpp \
#           src/gears/Gear_Blur.cpp \
#           src/gears/Gear_ColorAdjust.cpp \
#           src/gears/Gear_Contrast.cpp \
#           src/gears/Gear_ColorQuantize.cpp \
#           src/gears/Gear_ColorQuantizeWu.cpp \
#           src/gears/Gear_ClusteredDither.cpp \
#           src/gears/Gear_DataOut.cpp \
#           src/gears/Gear_DiffDist.cpp \
#           src/gears/Gear_Edge.cpp \
#           src/gears/Gear_Enveloppe.cpp \
#           src/gears/Gear_FilterSignal.cpp \
#           src/gears/Gear_FreqBoxes.cpp \
#           src/gears/Gear_Gain.cpp \
           src/gears/Gear_GrayScale.cpp \
#           src/gears/Gear_HalfToning.cpp \
#           src/gears/Gear_Image.cpp \
#           src/gears/Gear_KDTree.cpp \
#           src/gears/Gear_MasterFrequency.cpp \
#           src/gears/Gear_MedianFilter.cpp \
#           src/gears/Gear_NGone.cpp \
#           src/gears/Gear_Osc.cpp \
#           src/gears/Gear_Oscilloscope.cpp \
#           src/gears/Gear_PatternGen.cpp \
#           src/gears/Gear_Saturation.cpp \
#           src/gears/Gear_SimpleDelay.cpp \
#           src/gears/Gear_Slider.cpp \
#           src/gears/Gear_TV.cpp \
#           src/gears/Gear_VideoAdd.cpp \
#           src/gears/Gear_VideoBlend.cpp \
           src/gears/Gear_VideoInput.cpp \
#           src/gears/Gear_VideoMix.cpp \
           src/gears/Gear_VideoOutput.cpp \
           src/gears/Gear_VideoSource.cpp \
           src/GearGui.cpp \
#           src/GearGui_Slider.cpp \
#           src/GearGui_TV.cpp \
           src/GearMaker.cpp \
           src/GearPropertiesDialog.cpp \
           src/MainWindow.cpp \
           src/AbstractPlug.cpp \
	   src/Plug.cpp \
           src/PlugBox.cpp \
#           src/PlugSignalIn.cpp \
#           src/PlugSignalOut.cpp \
#           src/PlugVideoIn.cpp \
#           src/PlugVideoOut.cpp \
           src/Properties.cpp \
           src/PropertyControl.cpp \
           src/PropertyControlFilename.cpp \
           src/PropertyControlString.cpp \
	   src/PropertyControlBool.cpp \
#           src/Rasterer.cpp \
           src/SchemaEditor.cpp \
#           src/SignalCircularBuffer.cpp \
           src/SignalInfo.cpp \
           src/SummedAreaTable.cpp \
           src/Timing.cpp \
           src/VideoInfo.cpp \	   
	   src/VideoOutputMaker.cpp \
	   src/VideoOutputX11Base.cpp \
	   src/VideoOutputXv.cpp \
	   src/VideoOutputGl.cpp \
	   src/VideoOutputShm.cpp

