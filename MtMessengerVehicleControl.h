#ifndef _MT_MESSENGER_VEHICLE_CONTROL_
#define _MT_MESSENGER_VEHICLE_CONTROL_

#include "driver/mcpwm.h"

typedef struct {
  const mcpwm_config_t *configuration;
  mcpwm_unit_t unit;
  mcpwm_timer_t timer;
  mcpwm_io_signals_t io_signal_a;
  mcpwm_io_signals_t io_signal_b;
  uint8_t gpio_pwm_a;
  uint8_t gpio_pwm_b;
  uint8_t AIN_1;
  uint8_t AIN_2;
  uint8_t BIN_1;
  uint8_t BIN_2;
  mcpwm_generator_t gen_a;
  mcpwm_generator_t gen_b;
} mt_messenger_motor_t;


void mtMessengerVehicleControlInit(mt_messenger_motor_t *motors);

void mtMessengerVehicleControlFeed(
  mt_messenger_motor_t *motors,
  float duty_a,
  float duty_b
);


#endif