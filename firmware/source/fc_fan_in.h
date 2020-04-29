#pragma once

#include <stdint.h>

void fan_in_init(void);
uint16_t fan_in_get_duty_cycle(int i);
const char *fan_in_get_name(int i);
