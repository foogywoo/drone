#ifndef GEAR_VALUEFLATSIGNAL_INCLUDED
#define GEAR_VALUEFLATSIGNAL_INCLUDED

#include "GearConverter.h"
#include "types/SignalType.h"
#include "types/ValueType.h"

/**
 * Generates a flat signal, that is, a signal with a constant value. Can be used more
 * generally as a converter from <code>ValueType</code> to <code>SignalType</code>.
 * 
 * @author Jean-S�bastien Sen�cal
 * @version %I% %G%
 */
class Gear_FlatSignal : public GearConverter<ValueType, SignalType>
{
public:
  //! Default constructor.
  Gear_FlatSignal(Engine *engine, std::string name);

  // Destructor.
  virtual ~Gear_FlatSignal() {}

  void convert();
};


#endif
