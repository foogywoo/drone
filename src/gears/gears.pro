include(../../config.pro)

TEMPLATE=subdirs
SUBDIRS= Osc \
TV \
Oscilloscope \
VideoOutput \
#AudioPushButton \
AlphaMix \
Blur \
Slider \
KDTree\ 
VideoMix \
Edge \
AffineTransform \
ApplyDisplaceGrid \
AreaClip \
AreaCreate \
AreaScale \
AreaTranslate \
AreaVideoSelect \
AreaVideoReplace \
#AreaArrayMask \
#AreaArrayClip \
#AreaArrayVideoSelect \
Brightness \
ClusteredDither \
ColorAdjust \
Contrast \
Enveloppe \
EmptyImage \
FlatSignal \
FillAlpha \
ListBox \
ImageCapture \
ImageToTexture \
PushButton \
Rescale \
TouchPad \
TapTempo \
ColorQuantize \
Gamma \
GenDisplaceGrid \
GrayScale \
HalfToning \
#EmptyImage \
#ImageSource \
#ImageSequence \
Invert \
InvertAlpha \
PackList \
UnpackList \
#OscMessage \
#OscInput \
#OscOutput \
#OscFilter \
Saturation \
#SelectFrame \
SetAlpha \
ShaderTest \
SignalStat \
SmearGrid \
Sobel \
StringOutput \
#StringGen \
StringFormat \
StringSource \
RandomValue \
Tempo \
ValueClamp \
VideoDelay \
#VideoInput \
VideoRecord \
VideoSource \
VideoOffset \
#VideoReplaceAreas \
VideoSwitch \
ValueMix
agg {
SUBDIRS+= SVGLoader \
Vectorial2Raster \
VecAffineTrans
}

#linux specific gears
#unix:!macx:SUBDIRS += VideoInput AudioInput
unix:!macx:SUBDIRS += VideoInput

