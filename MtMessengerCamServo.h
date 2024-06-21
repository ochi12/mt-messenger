#ifndef _MT_MESSENGER_CAM_SERVO_
#define _MT_MESSENGER_CAM_SERVO_

#include <ESP32Servo.h>
#include <sys/_stdint.h>

class MtMessengerCamServo {
  private:
    Servo tiltServo;
    Servo yawServo;

    uint8_t tiltAngle;
    uint8_t yawAngle;

    unsigned long tiltOldMillis = 0;
    unsigned long yawOldMillis = 0;

  public:

  void begin(uint8_t tiltPin, uint8_t yawPin, uint8_t _tiltAngle, uint8_t _yawAngle);
  void feedDigital(bool camLeft, bool camRight, bool camUp, bool camDown);
  void feedAnalog(int __tilt_angle, int __yaw_angle);

};

#endif