#include "Gear_Slider.h"
#include "GearMaker.h"
#include "GearGui_Slider.h"
#include "Math.h"

#include "Engine.h"

#include <qdom.h>
#include <iostream>
#include <sstream>

Register_Gear(MAKERGear_Slider, Gear_Slider, "Slider")

const float  Gear_Slider::DEFAULT_VALUE = 1.0f;

const std::string Gear_Slider::SETTING_LOWERBOUND = "Lower Bound";
const std::string Gear_Slider::SETTING_HIGHERBOUND = "Higher Bound";

Gear_Slider::Gear_Slider(Engine *engine, std::string name) : Gear(engine, "Slider", name),_acceptHint(true)
{

  addPlug(_VALUE_OUT = new PlugOut<ValueType>(this, "Value"));

  _settings.add(Property::FLOAT, SETTING_HIGHERBOUND)->valueFloat(100.0f);
  _settings.add(Property::FLOAT, SETTING_LOWERBOUND)->valueFloat(0.0f);

  setValue(DEFAULT_VALUE);

}

Gear_Slider::~Gear_Slider()
{

}

bool Gear_Slider::ready()
{
  return(_VALUE_OUT->connected());
}

void Gear_Slider::onUpdateSettings()
{
  //validation
  float low = _settings.get(Gear_Slider::SETTING_LOWERBOUND)->valueFloat();
  float hi = _settings.get(Gear_Slider::SETTING_HIGHERBOUND)->valueFloat();    
  if (low>hi)
  {
    _settings.get(Gear_Slider::SETTING_LOWERBOUND)->valueFloat(hi);
    _settings.get(Gear_Slider::SETTING_HIGHERBOUND)->valueFloat(low);    
  }

  //range have changed
  //set the value, to force clamping if needed
  setValue(getValue());

  //then we need to redraw the gearGui
  getGearGui()->reDraw();

}

void Gear_Slider::onPlugConnected(AbstractPlug *plug)
{
  if (plug == _VALUE_OUT && _acceptHint)
  {
    ValueType *tmpType = dynamic_cast<ValueType*>(plug->firstConnectedPlug()->abstractHintType());
    _settings.get(Gear_Slider::SETTING_LOWERBOUND)->valueFloat(tmpType->minValue()); 
    _settings.get(Gear_Slider::SETTING_HIGHERBOUND)->valueFloat(tmpType->maxValue());
    setValue(tmpType->value());
    onUpdateSettings();
  }
}

void Gear_Slider::onPlugDisconnected(AbstractPlug* plug)
{
   if (plug == _VALUE_OUT)
     _acceptHint=true;
} 


void Gear_Slider::setValue(float value)
{
  //clamp value to range
  float low = _settings.get(Gear_Slider::SETTING_LOWERBOUND)->valueFloat();
  float hi = _settings.get(Gear_Slider::SETTING_HIGHERBOUND)->valueFloat();    

  value = CLAMP(value, low, hi);

  _VALUE_OUT->type()->setValue(value);
}

void Gear_Slider::runAudio()
{

}

GearGui *Gear_Slider::createGearGui(QCanvas *canvas)
{                
  return new GearGui_Slider(this, canvas);
}

void Gear_Slider::save(QDomDocument &doc, QDomElement &gearElem)
{
  std::ostringstream strValue;

  strValue << getValue();
  QDomAttr attrSliderPos = doc.createAttribute("SliderPos");
  attrSliderPos.setValue(strValue.str().c_str());
  gearElem.setAttributeNode(attrSliderPos);

}

void Gear_Slider::load(QDomElement &gearElem)
{
  setValue(gearElem.attribute("SliderPos","").toFloat());        
  _acceptHint=false;
}

