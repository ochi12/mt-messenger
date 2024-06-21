// #include "BluetoothSerial.h"

#include "MtMessengerVehicleControl.h"
#define YAW_MIN 20
#define YAW_MAX 180
#define TILT_MIN 1
#define TILT_MAX 120
#include "MtMessengerCamServo.h"
#include "MtMessengerCommsBL.h"
#include "MtMessengerProximity.h"


const char *pin = "12345678"; // Change this to more secure PIN.

String device_name = "mt. messenger";


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif


#define TILT_PIN 32
#define YAW_PIN 33

#define TRIG_PIN 26
#define ECHO_PIN 27



// motor macros
#define GPIO_PWM0A_OUT 16 //right
#define AIN1 17
#define AIN2 5

#define STANDBY 18

#define BIN1 19
#define BIN2 22
#define GPIO_PWM0B_OUT 23 //right






mt_messenger_motor_t motors;


// BluetoothSerial SerialBT;
MtMessengerCamServo cameraServo;
MtMessengerCommsBL commsBL;
MtMessengerProximity proximity;


//starting value of servos
uint8_t tiltAngle = 80;
uint8_t yawAngle = 75;
String packet;


unsigned long oldMillis = 0;



void proximityISR() {
  proximity.mtMessengerProximityISR();
}

void setup() {
  Serial.begin(115200);
  // SerialBT.begin(device_name); 
  // SerialBT.setPin(pin);
  // SerialBT.setTimeout(5);


  //MtMessengerCameraServo initialize
  cameraServo.begin(TILT_PIN, YAW_PIN, tiltAngle, yawAngle);
  commsBL.begin(device_name, 5);
  proximity.begin(TRIG_PIN, ECHO_PIN, proximityISR);

  mcpwm_config_t config;
  config.frequency = 1000;
  config.cmpr_a = 0;
  config.cmpr_b = 0;
  config.counter_mode = MCPWM_UP_COUNTER;
  config.duty_mode = MCPWM_DUTY_MODE_0;

  motors.configuration = &config;
  motors.gpio_pwm_a = GPIO_PWM0A_OUT;
  motors.gpio_pwm_b = GPIO_PWM0B_OUT;
  motors.io_signal_a = MCPWM0A;
  motors.io_signal_b = MCPWM0B;
  motors.AIN_1 = AIN1;
  motors.AIN_2 = AIN2;
  motors.BIN_1 = BIN1;
  motors.BIN_2 = BIN2;
  motors.unit = MCPWM_UNIT_0;
  motors.timer = MCPWM_TIMER_0;
  motors.gen_a = MCPWM_OPR_A;
  motors.gen_b = MCPWM_OPR_B;

  pinMode(STANDBY, OUTPUT);
  digitalWrite(STANDBY, HIGH);

  mtMessengerVehicleControlInit(&motors);

  while(!commsBL.has_client()); // wait for connection

}

void loop() {

  mt_messenger_comms_bl_event_t bl_event;
  commsBL.decodePacket(commsBL.getPacket(), &bl_event);

  
  if (!bl_event.horn_state) {
    // cameraServo.feedDigital(commsBL.camLeftState(), commsBL.camRightState(), commsBL.camUpState(), commsBL.camDownState());
    cameraServo.feedDigital(bl_event.cam_left_state, bl_event.cam_right_state, bl_event.cam_up_state, bl_event.cam_down_state);

    float mapped_left = map(bl_event.r_motor_val, -65536, 65536, -100, 100);
    float mapped_right = map(bl_event.l_motor_val, -65536, 65536, -100, 100);
    mtMessengerVehicleControlFeed(&motors, mapped_right, mapped_left);

    Serial.print(mapped_right);
    Serial.print(" : ");
    Serial.println(mapped_left);



    // implement motot control later
  } else {
    float tilt = map(bl_event.l_motor_val, -65536, 65536, TILT_MIN, TILT_MAX);
    float yaw = map(bl_event.r_motor_val, -65536, 65536, YAW_MIN, YAW_MAX);
    cameraServo.feedAnalog(
      tilt,
      yaw
    );
  }


  if(millis() - oldMillis > 150) {
    oldMillis = millis();
    commsBL.sendPacket(proximity.getDistance());
  }

  proximity.clearTrigger();


  if(!commsBL.has_client()) {
    esp_restart();
  }

}


float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



