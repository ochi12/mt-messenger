#include "HardwareSerial.h"
#include "MtMessengerCommsBL.h"

void MtMessengerCommsBL::begin(String device_name, int timeout){
  SerialBT.begin(device_name); 
  // SerialBT.setPin(pin);
  SerialBT.setTimeout(timeout);
}

String MtMessengerCommsBL::getPacket() {
  if (SerialBT.available()) {
    _packet = SerialBT.readString();
  } 
  return _packet;
}

void MtMessengerCommsBL::sendPacket(float packet) {
  // if (SerialBT.availableForWrite()) {
    SerialBT.println(packet);
  
} 


void MtMessengerCommsBL::decodePacket(String packet, mt_messenger_comms_bl_event_t *bl_event) {
  #ifndef COMMS_BL_DELIMETER
  #define COMMS_BL_DELIMETER ":"
  #endif

  d  = packet.indexOf(":");
  d1 = packet.indexOf(":", d + 1);
  d2 = packet.indexOf(":", d1 + 1);
  d3 = packet.indexOf(":", d2 + 1);
  d4 = packet.indexOf(":", d3 + 1);
  d5 = packet.indexOf(":", d4 + 1);
  d6 = packet.indexOf(":", d5 + 1);
  d7 = packet.indexOf(":", d6 + 1);
  d8 = packet.indexOf(":", d7 + 1);
  d9 = packet.indexOf(":", d8 + 1);
  
  // lMotor = packet.substring(d+1, d1).toInt();
  // rMotor = packet.substring(d1+1, d2).toInt();
  // fLight = packet.substring(d2+1, d3).toInt();
  // horn = packet.substring(d3+1, d4).toInt();
  // camUp = packet.substring(d4+1, d5).toInt();
  // camDown = packet.substring(d5+1, d6).toInt();
  // camLeft = packet.substring(d6+1, d7).toInt();
  // camRight = packet.substring(d7+1, d8).toInt();
  // fIntensity = packet.substring(d8+1, d9).toInt();

  bl_event->l_motor_val = packet.substring(d+1, d1).toInt();
  bl_event->r_motor_val = packet.substring(d1+1, d2).toInt();
  bl_event->f_ligth_state = packet.substring(d2+1, d3).toInt();
  bl_event->horn_state = packet.substring(d3+1, d4).toInt();
  bl_event->cam_up_state = packet.substring(d4+1, d5).toInt();
  bl_event->cam_down_state = packet.substring(d5+1, d6).toInt();
  bl_event->cam_left_state = packet.substring(d6+1, d7).toInt();
  bl_event->cam_right_state = packet.substring(d7+1, d8).toInt();
  bl_event->f_light_intensity_val = packet.substring(d8+1, d9).toInt();

}

bool MtMessengerCommsBL::has_client() {
  return SerialBT.hasClient();
}

// int MtMessengerCommsBL::getLMotorVal() { return lMotor; }
// int MtMessengerCommsBL::getRMotorVal() { return rMotor; }
// bool MtMessengerCommsBL::fLightState() { return fLight; } 
// bool MtMessengerCommsBL::hornState() { return horn; }
// bool MtMessengerCommsBL::camUpState() {  return camUp; }
// bool MtMessengerCommsBL::camDownState() {  return camDown; }
// bool MtMessengerCommsBL::camLeftState() {  return camLeft; }
// bool MtMessengerCommsBL::camRightState() {  return camRight; }
// int MtMessengerCommsBL::fIntensityVal() {  return fIntensity; }