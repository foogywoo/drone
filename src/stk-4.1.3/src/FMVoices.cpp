/***************************************************/
/*! \class FMVoices
    \brief STK singing FM synthesis instrument.

    This class implements 3 carriers and a common
    modulator, also referred to as algorithm 6 of
    the TX81Z.

    \code
    Algorithm 6 is :
                        /->1 -\
                     4-|-->2 - +-> Out
                        \->3 -/
    \endcode

    Control Change Numbers: 
       - Vowel = 2
       - Spectral Tilt = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha.  If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2002.
*/
/***************************************************/

#include "FMVoices.h"
#include "SKINI.msg"
#include "Phonemes.h"

FMVoices :: FMVoices()
  : FM()
{
  // Concatenate the STK rawwave path to the rawwave files
  for ( int i=0; i<3; i++ )
    waves[i] = new WaveLoop( (Stk::rawwavePath() + "sinewave.raw").c_str(), TRUE );
  waves[3] = new WaveLoop( (Stk::rawwavePath() + "fwavblnk.raw").c_str(), TRUE );

  this->setRatio(0, 2.00);
  this->setRatio(1, 4.00);
  this->setRatio(2, 12.0);
  this->setRatio(3, 1.00);

  gains[3] = __FM_gains[80];

  adsr[0]->setAllTimes( 0.05, 0.05, __FM_susLevels[15], 0.05);
  adsr[1]->setAllTimes( 0.05, 0.05, __FM_susLevels[15], 0.05);
  adsr[2]->setAllTimes( 0.05, 0.05, __FM_susLevels[15], 0.05);
  adsr[3]->setAllTimes( 0.01, 0.01, __FM_susLevels[15], 0.5);

  twozero->setGain( 0.0 );
  modDepth = (MY_FLOAT) 0.005;
  currentVowel = 0;
  tilt[0] = 1.0;
  tilt[1] = 0.5;
  tilt[2] = 0.2;    
  mods[0] = 1.0;
  mods[1] = 1.1;
  mods[2] = 1.1;
  baseFrequency = 110.0;
  setFrequency( 110.0 );    
}  

FMVoices :: ~FMVoices()
{
}

void FMVoices :: setFrequency(MY_FLOAT frequency)
{
  MY_FLOAT temp, temp2 = 0.0;
  int tempi = 0;
  unsigned int i = 0;

  if (currentVowel < 32)	{
    i = currentVowel;
    temp2 = (MY_FLOAT) 0.9;
  }
  else if (currentVowel < 64)	{
    i = currentVowel - 32;
    temp2 = (MY_FLOAT) 1.0;
  }
  else if (currentVowel < 96)	{
    i = currentVowel - 64;
    temp2 = (MY_FLOAT) 1.1;
  }
  else if (currentVowel <= 128)	{
    i = currentVowel - 96;
    temp2 = (MY_FLOAT) 1.2;
  }

  baseFrequency = frequency;
  temp = (temp2 * Phonemes::formantFrequency(i, 0) / baseFrequency) + 0.5;
  tempi = (int) temp;
  this->setRatio(0,(MY_FLOAT) tempi);
  temp = (temp2 * Phonemes::formantFrequency(i, 1) / baseFrequency) + 0.5;
  tempi = (int) temp;
  this->setRatio(1,(MY_FLOAT) tempi);
  temp = (temp2 * Phonemes::formantFrequency(i, 2) / baseFrequency) + 0.5;
  tempi = (int) temp;
  this->setRatio(2, (MY_FLOAT) tempi);    
  gains[0] = 1.0;
  gains[1] = 1.0;
  gains[2] = 1.0;
}

void FMVoices :: noteOn(MY_FLOAT frequency, MY_FLOAT amplitude)
{
  this->setFrequency(frequency);
  tilt[0] = amplitude;
  tilt[1] = amplitude * amplitude;
  tilt[2] = tilt[1] * amplitude;
  this->keyOn();

#if defined(_STK_DEBUG_)
  std::cerr << "FMVoices: NoteOn frequency = " << frequency << ", amplitude = " << amplitude << std::endl;
#endif
}

MY_FLOAT FMVoices :: tick()
{
  register MY_FLOAT temp, temp2;

  temp = gains[3] * adsr[3]->tick() * waves[3]->tick();
  temp2 = vibrato->tick() * modDepth * (MY_FLOAT) 0.1;

  waves[0]->setFrequency(baseFrequency * (1.0 + temp2) * ratios[0]);
  waves[1]->setFrequency(baseFrequency * (1.0 + temp2) * ratios[1]);
  waves[2]->setFrequency(baseFrequency * (1.0 + temp2) * ratios[2]);
  waves[3]->setFrequency(baseFrequency * (1.0 + temp2) * ratios[3]);

  waves[0]->addPhaseOffset(temp * mods[0]);
  waves[1]->addPhaseOffset(temp * mods[1]);
  waves[2]->addPhaseOffset(temp * mods[2]);
  waves[3]->addPhaseOffset(twozero->lastOut());
  twozero->tick(temp);
  temp =  gains[0] * tilt[0] * adsr[0]->tick() * waves[0]->tick();
  temp += gains[1] * tilt[1] * adsr[1]->tick() * waves[1]->tick();
  temp += gains[2] * tilt[2] * adsr[2]->tick() * waves[2]->tick();
    
  return temp * 0.33;
}

void FMVoices :: controlChange(int number, MY_FLOAT value)
{
  MY_FLOAT norm = value * ONE_OVER_128;
  if ( norm < 0 ) {
    norm = 0.0;
    std::cerr << "FMVoices: Control value less than zero!" << std::endl;
  }
  else if ( norm > 1.0 ) {
    norm = 1.0;
    std::cerr << "FMVoices: Control value greater than 128.0!" << std::endl;
  }


  if (number == __SK_Breath_) // 2
    gains[3] = __FM_gains[(int) ( norm * 99.9 )];
  else if (number == __SK_FootControl_)	{ // 4
    currentVowel = (int) (norm * 128.0);
    this->setFrequency(baseFrequency);
  }
  else if (number == __SK_ModFrequency_) // 11
    this->setModulationSpeed( norm * 12.0);
  else if (number == __SK_ModWheel_) // 1
    this->setModulationDepth( norm );
  else if (number == __SK_AfterTouch_Cont_)	{ // 128
    tilt[0] = norm;
    tilt[1] = norm * norm;
    tilt[2] = tilt[1] * norm;
  }
  else
    std::cerr << "FMVoices: Undefined Control Number (" << number << ")!!" << std::endl;

#if defined(_STK_DEBUG_)
  std::cerr << "FMVoices: controlChange number = " << number << ", value = " << value << std::endl;
#endif
}
