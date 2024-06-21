#include "Arduino.h"
#include "MtMessengerCamServo.h"


void MtMessengerCamServo::begin(uint8_t tiltPin, uint8_t yawPin, uint8_t _tiltAngle, uint8_t _yawAngle) {
  tiltServo.attach(tiltPin);
  yawServo.attach(yawPin);

  yawAngle = _yawAngle;
  tiltAngle = _tiltAngle;

  tiltServo.write(tiltAngle);
  yawServo.write(yawAngle);

}

void MtMessengerCamServo::feedDigital(bool camLeft, bool camRight, bool camUp, bool camDown) {

  #ifndef SERVO_DELAY
  #define SERVO_DELAY 2
  #endif

 
  if (millis() - tiltOldMillis > SERVO_DELAY) {
    tiltOldMillis = millis();
    if (camUp) {
      tiltAngle--;
  
    } 
    if (camDown) {
      tiltAngle++;
      
    }

    yawOldMillis = millis();
    if (camLeft) {
     yawAngle++;
  
    } 
    if (camRight) {
      yawAngle--;
      
    }
  }


  #ifndef YAW_MIN
  #define YAW_MIN 1
  #endif
  #ifndef YAW_MAX
  #define YAW_MAX 180
  #endif

  #ifndef TILT_MIN
  #define TILT_MIN 1
  #endif
  #ifndef TILT_MAX
  #define TILT_MAX 150
  #endif

  yawAngle = constrain(yawAngle, YAW_MIN, YAW_MAX);
  tiltAngle = constrain(tiltAngle, TILT_MIN, TILT_MAX);

  yawServo.write(yawAngle);
  tiltServo.write(tiltAngle);
}

void MtMessengerCamServo::feedAnalog(int __tilt_angle, int __yaw_angle) {
  yawServo.write(__yaw_angle);
  tiltServo.write(__tilt_angle);
}

