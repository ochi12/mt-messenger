#include "HardwareSerial.h"
#include "driver/mcpwm_types_legacy.h"
#include "Print.h"
#include <vector>
#include "esp32-hal-gpio.h"
#include "driver/mcpwm.h"
#include <stdio.h>
#include <cstdlib>
#include "MtMessengerVehicleControl.h"


void mtMessengerVehicleControlInit(mt_messenger_motor_t *motors) {

  mcpwm_gpio_init(motors->unit, motors->io_signal_a, motors->gpio_pwm_a);
  mcpwm_gpio_init(motors->unit, motors->io_signal_b, motors->gpio_pwm_b);
  mcpwm_init(motors->unit, motors->timer, motors->configuration);

  // initially no motors running
  std::vector<uint8_t> pins = {motors->AIN_1, motors->AIN_2, motors->BIN_1, motors->BIN_2};
  for (uint8_t pin: pins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

}

void mtMessengerVehicleControlFeed(mt_messenger_motor_t *motors, float duty_a, float duty_b) {
  
  // Motor A control signal

  int a, b, c, d;

  a = duty_a > 0;
  b = duty_a < 0;
  c = duty_b > 0;
  d = duty_b < 0;



  digitalWrite(motors->AIN_1, (duty_a > 0) ? HIGH : LOW);
  digitalWrite(motors->AIN_2, (duty_a < 0) ? HIGH : LOW);

  

  // Motor B control signal
  digitalWrite(motors->BIN_1, (duty_b > 0) ? HIGH : LOW);
  digitalWrite(motors->BIN_2, (duty_b < 0) ? HIGH : LOW);

  // speed set
  duty_a = abs(duty_a);
  duty_b = abs(duty_b);

  if (duty_a == 0) {
    mcpwm_set_signal_low(motors->unit, motors->timer, motors->gen_a);
  } else {
    mcpwm_set_duty_type(motors->unit, motors->timer, motors->gen_a, MCPWM_DUTY_MODE_0);
    mcpwm_set_duty(motors->unit, motors->timer, motors->gen_a, duty_a);
  }

  if (duty_b == 0) {
    mcpwm_set_signal_low(motors->unit, motors->timer, motors->gen_b);
  } else {
    mcpwm_set_duty_type(motors->unit, motors->timer, motors->gen_b, MCPWM_DUTY_MODE_0);
    mcpwm_set_duty(motors->unit, motors->timer, motors->gen_b, duty_b); 
  }




}