#include "soc/soc.h"
#ifndef _MT_MESSENGER_COMMS_BL_
#define _MT_MESSENGER_COMMS_BL_

#include "BluetoothSerial.h"
#include <sys/_stdint.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
// lMotor, rMotor, fLight, horn, camUp, camDown, camLeft, camRight, fIntensity
#define L_MOTOR 0
#define R_MOTOR 1
#define F_LIGHT 2
#define HORN    3
#define CAM_UP  4
#define CAM_DOWN 5
#define CAM_LEFT 6
#define CAM_RIGHT 7
#define F_INTENSITY 8

typedef struct {
  int l_motor_val;
  int r_motor_val;
  bool f_ligth_state;
  bool horn_state;
  bool cam_up_state;
  bool cam_down_state;
  bool cam_left_state;
  bool cam_right_state;
  int f_light_intensity_val;
} mt_messenger_comms_bl_event_t;

class MtMessengerCommsBL {
  private:

  BluetoothSerial SerialBT;
  String _packet;

  int d, d1, d2, d3, d4, d5 , d6, d7, d8, d9; // these are uninitialized variables for the indexes of the given delimeter
  int lMotor, rMotor, fLight, horn, camUp, camDown, camLeft, camRight, fIntensity; // decoded values are stored here

  public:

  void  begin(String device_name,  int timeout);
  String getPacket();
  void sendPacket(float packet);
  void decodePacket(String packet, mt_messenger_comms_bl_event_t *pin);
  bool has_client();
  // int getLMotorVal();
  // int getRMotorVal();
  // bool fLightState();
  // bool hornState();
  // bool camUpState();
  // bool camDownState();
  // bool camLeftState();
  // bool camRightState();
  // int fIntensityVal();

};

#endif