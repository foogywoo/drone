 /* Gear_BeatDetector.h
 * Copyright (C) 2005 Norman Casagrande, Jean-Sebastien Senecal
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

#ifndef GEAR_VALUEFLATSIGNAL_INCLUDED
#define GEAR_VALUEFLATSIGNAL_INCLUDED

#include "GearConverter.h"
#include "types/SignalType.h"
#include "types/ValueType.h"

#include "VideoRGBAType.h"

#include "CircularArray.h"

/**
 * Generates a flat signal, that is, a signal with a constant value. Can be used more
 * generally as a converter from <code>ValueType</code> to <code>SignalType</code>.
 * 
 * @author Norman Casagrande
 * @author Jean-S�bastien Sen�cal
 * @version %I% %G%
 */
class Gear_BeatDetector : public Gear
{
public:
  //! Default constructor.
  Gear_BeatDetector(Schema *schema, std::string uniqueName);

  // Destructor.
  virtual ~Gear_BeatDetector() {}

  bool ready();
  void runAudio();
  
private:

  inline void addSample(float sample); // add sample to buffer and autocorrelation
  inline void applyDecay();

  PlugIn<SignalType>*   _AUDIO_IN;
  
  PlugOut<VideoRGBAType> *_ACORR_VIDEO_OUT;
  VideoRGBAType*          _pOutImage;
  void                    drawACorr();
  
  CircularArray<float>  _buffer;
  CircularArray<float>::iterator _sampleIt;
  CircularArray<float>::iterator _sampleLaggedIt;

  Array<float>          _autoCorrelation;
  float*                _pAutoCorrelation;
	
	Array<float>					_downSampledSig;
	float*                _pDownSampledSig;
	
	float                 _smoothSampleAverage;  
	float                 _smoothDecay;
	
  unsigned int          _minLag;
  unsigned int          _maxLag;
  unsigned int          _rangeSize;
  unsigned int          _acorrSize;
  
  float                 _acorrDecay;
  unsigned int          _acorrDecayCounter;
  unsigned int          _acorrDecayStep;
  
  
  unsigned int  _dbgStep;
  unsigned int  _dbgSize;
};


template <typename T, typename ItSource, typename ItDest>
  void downsample(ItDest dest, size_t dest_size, ItSource source, size_t source_size)
{
  double filters[] = { 0.05, 0.1, 0.7, 0.1, 0.05 };
  size_t filters_size = 5;
  size_t rate = (size_t)( (double)source_size / (double)(dest_size) + 0.499 );
  
  bool addTail = false;

  if (rate != (size_t)( (double)source_size / (double)(dest_size)) )
    --rate;
  else
    addTail = true;

  size_t i, j;
  double sum;
  size_t destCounter = 0;

  size_t sourcePos = 0;
  
  size_t max_size = source_size - filters_size;
  
  for (i = 0; i < max_size ; i += rate )
  {
    sum = 0;
    ItSource currPos = source;
    
    for (j = 0; j < filters_size; ++j)
      sum += filters[j] * *(currPos++);
    
    *(dest++) = sum;

    // fix that!
    ++destCounter;
    if (destCounter >= dest_size)
      return;
    
    for (j = 0; j < rate; ++j)
    {
      ++sourcePos;
      ++source;
    }
  }

  if (addTail)
  {
    size_t goBack = source_size % filters_size;
    for (i = 0; i < goBack; ++i)
      --source;

    sum = 0;
    for (j = 0; j < filters_size; ++j)
      sum += filters[j] * *(source++);
    *dest = sum;
  }
}


template <typename T, typename Iterator>
  void smooth(Iterator source, size_t source_size, float decay, float& average)
{
  float one_minus_decay = 1.0f - decay;
  size_t i;
  Iterator head = source;
    
  for (i = 0; i < source_size; ++i, ++source)
  {
    *source = decay * *source + one_minus_decay * average;
    average = *source;
//    *source *= decay;
//    *source += one_minus_decay * average;
//    average = *source;
  }   
  
}

#endif
