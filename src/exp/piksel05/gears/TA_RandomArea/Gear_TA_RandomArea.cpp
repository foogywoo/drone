/* Gear_TA_RandomArea.cpp
 * Copyright (C) 2004 Mathieu Guindon, Julien Keable
 * This file is part of Drone.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include "Gear_TA_RandomArea.h"
#include "Engine.h"

#include "GearMaker.h"

#include "Random.h"
#include "Math.h"

extern "C" {
Gear* makeGear(Schema *schema, std::string uniqueName)
{
  return new Gear_TA_RandomArea(schema, uniqueName);
}

GearInfo getGearInfo()
{
  GearInfo gearInfo;
  gearInfo.name = "TA_RandomArea";
  gearInfo.classification = GearClassifications::unclassified().instance();
  return gearInfo;
}
}

Gear_TA_RandomArea::Gear_TA_RandomArea(Schema *schema, std::string uniqueName) : 
  Gear(schema, "TA_RandomArea", uniqueName)
{
  addPlug(_NEXT = new PlugIn<ValueType>(this, "Next", false, new ValueType(1, 0, 1)));
  addPlug(_AREA = new PlugOut<AreaType>(this, "Area", false));
  Random::seed();
}

Gear_TA_RandomArea::~Gear_TA_RandomArea()
{

}

void Gear_TA_RandomArea::runVideo()
{
  if (_NEXT->type()->boolValue())
  {
    _AREA->type()->setOrigin((int)( CLAMP(Random::uniform(), 0.0f, 1.0f) * WINDOW_WIDTH/2),
                             (int)( CLAMP(Random::uniform(), 0.0f, 1.0f) * WINDOW_HEIGHT/2));
    _AREA->type()->resize((size_t)MAX( Random::uniform() * WINDOW_HEIGHT/2, 32.0f),
                          (size_t)MAX( Random::uniform() * WINDOW_HEIGHT/2, 32.0f));
//     _AREA->type()->setOrigin((int)( CLAMP(Random::normal(0,1), 0.0f, 1.0f) * WINDOW_WIDTH/2),
//                              (int)( CLAMP(Random::normal(0,1), 0.0f, 1.0f) * WINDOW_HEIGHT/2));
//     _AREA->type()->resize((size_t)MAX( CLAMP(Random::normal(0,1), 0.0f, 1.0f) * WINDOW_WIDTH/2, 32.0f),
//                           (size_t)MAX( CLAMP(Random::normal(0,1), 0.0f, 1.0f) * WINDOW_HEIGHT/2, 32.0f));
//    _AREA->type()->debug();
  }
}

