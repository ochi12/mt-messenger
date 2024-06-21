#include "Arduino.h"
#include "FunctionalInterrupt.h"
#include <sys/_intsup.h>

#include "MtMessengerProximity.h"


void MtMessengerProximity::mtMessengerProximityISR() {
  switch (digitalRead(echoPin)) {
    case 1:
      start = micros();
      break;
    case 0:
      end = micros();
      break;
  }
}


void MtMessengerProximity::begin(uint8_t trigPin, uint8_t echoPin, std::function<void ()> intRoutine) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  attachInterrupt(echoPin, intRoutine, CHANGE);

  this->trigPin = trigPin;
  this->echoPin = echoPin;

}


unsigned long MtMessengerProximity::getDistance() {
  
  duration = end - start;
  return constrain((duration/2) * SOUND_SPEED,0, 200);
}

void MtMessengerProximity::clearTrigger() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
}

