#include <sys/_stdint.h>

#ifndef _MT_MESSENGER_PROXIMITY_
#define _MT_MESSENGER_PROXIMITY_
#define SOUND_SPEED 0.0343 // centimeter/microsecond

#include "FunctionalInterrupt.h"
#include "esp32-hal-gpio.h"


class MtMessengerProximity {
  private:
  
  unsigned long duration;
  unsigned long start;
  unsigned long end;

  uint8_t echoPin, trigPin;
  
  public:
 
  void mtMessengerProximityISR();
  void begin(uint8_t trigPin, uint8_t echoPin, std::function<void ()> intRoutine);
  unsigned long getDistance();
  void clearTrigger();

  
};



#endif