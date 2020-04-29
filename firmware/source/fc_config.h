#pragma once

#include "hal.h"

enum ShellPort {
    ShellPort_USB,
    ShellPort_UART,
};

#define SHELL_PORT ShellPort_UART

#define EOL "\r\n"

struct FanPort {
    const char *name;
    _Bool is_4_pin;
    ioline_t pwm_line;
    ioline_t tacho_line;
    PWMDriver *pwm_driver;
    uint8_t pwm_channel;
};

#define FAN_PORT_COUNT 11
extern struct FanPort FAN_PORTS[];

#define FAN_4PIN_PWM_CLOCK 72000000
#define FAN_4PIN_PWM_PERIOD 500
#define FAN_3PIN_PWM_CLOCK 72000000
#define FAN_3PIN_PWM_PERIOD 500

// In milliseconds
#define TACHO_TIMER_PERIOD 500
#define CONTROL_TIMER_PERIOD 100

struct FanInPort {
    const char *name;
    ioline_t pwm_line;
    ioline_t tacho_line;
};

#define FAN_IN_PORT_COUNT 0
extern struct FanInPort FAN_IN_PORTS[];

#define FAN_IN_PWM_AVG_POINTS 8

#define TEMPSRC_VIRT_COUNT 4

#define FAN_GMAP_PTS 10
