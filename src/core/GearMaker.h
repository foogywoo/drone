/* GearMaker.h
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

#ifndef GEAR_MAKER_INCLUDED
#define GEAR_MAKER_INCLUDED

#include <map>
#include <string>
#include <vector>

#include "Gear.h"

class GearMaker  
{
public:
  enum eGearPluginType {DRONE_PLUGIN, FREI0R_PLUGIN};
  
  class GearPluginDefinition
  {
  public:
    GearPluginDefinition(GearInfo gearInfo, eGearPluginType pluginType, void *handle, Gear* (*pmakeGear)(Schema *schema, std::string uniqueName)) :
      makeGear(pmakeGear),
      _gearInfo(gearInfo),
      _pluginType(pluginType),
      _handle(handle)      
    {
    }

    const GearInfo& gearInfo() const {return _gearInfo;}
    eGearPluginType pluginType() const {return _pluginType;}
    const void* handle() const {return _handle;}
    
    //ptrfunc
    Gear* (*makeGear)(Schema *schema, std::string uniqueName);

  private:
    GearInfo _gearInfo;
    eGearPluginType _pluginType;
    void* _handle;
  };

  GearMaker();
  ~GearMaker();

  static Gear* makeGear(Schema *schema, std::string type, std::string uniqueName);
  static void getAllGearsInfo(std::vector<const GearInfo*> &gearsInfo);
  static void parseGears();
  static void parseFrei0rPlugins();
private:
  static std::map<std::string, GearMaker::GearPluginDefinition*> *_registry;
  static GearMaker _registerMyself;  
  static std::string droneGearsPath;
};

/*
#define Register_Gear(MMAKERNAME, MCLASSNAME, MTYPE) \
class MMAKERNAME : public GearMaker \
{ \
public: \
    MMAKERNAME() : GearMaker(MTYPE){}; \
private: \
    Gear* internalMakeGear(Schema *schema, std::string uniqueName) \
    { \
        return new MCLASSNAME(schema, uniqueName);\
    } \
    static MMAKERNAME _registerThis;\
};\
MMAKERNAME MMAKERNAME::_registerThis;
*/

#endif
