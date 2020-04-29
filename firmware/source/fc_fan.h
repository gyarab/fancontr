#pragma once

#include "fc_config.h"
#include "fc_gmap.h"

// Each percent is 100
#define DUTY_CYCLE_DECIMAL_PLACES 2

void fan_init_ports(void);
int fan_by_name(char *name);
// Duty cycle given in tenthousandths
void fan_set_duty_cycle(struct FanPort port, uint16_t duty);
uint16_t fan_get_rpm(int i);

void fan_init_control_blank(void);
void fan_set_tempsrc(int i_fan, int i_tempsrc);
void fan_set_gmap(
        int i, struct GmapPoint pts[FAN_GMAP_PTS], uint8_t pts_count);
struct GmapPoint *fan_get_gmap(int i);
uint8_t fan_get_gmap_pts_count(int i);
