//
//  TextureType.h
//  drone
//
//  Created by Mathieu Guindon on 2012-12-18.
/*
* Copyright (C) 2004 Mathieu Guindon, Julien Keable, Jean-Sebastien Senecal
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


#ifndef drone_TextureType_h
#define drone_TextureType_h

#include "AbstractType.h"
#include "VideoRGBAType.h"

#include <string>

class TextureType : public AbstractType
{
public:
  TextureType();
  
  virtual ~TextureType();

  virtual std::string typeName() const { return "Texture"; }
  virtual QColor color() const { return QColor(255, 255, 64); }
  
  void setTextureName(unsigned int value) { _textureName = value; }
  unsigned int textureName() const { return _textureName; }
  
  unsigned int createWithSize(int textureSizeX, int textureSizeY, bool forceCreation = false);
  unsigned int updateWithVideoRGBA(const VideoRGBAType &image);
  int textureSizeX() const {return _textureSizeX;}
  int textureSizeY() const {return _textureSizeY;}

  void setTextureSizeX(int value) {_textureSizeX = value;}
  void setTextureSizeY(int value) {_textureSizeY = value;}
  
private:
	unsigned int _textureName;
  int _textureSizeX;
  int _textureSizeY;
  
};

#endif
