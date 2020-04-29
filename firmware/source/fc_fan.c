#include "fc_fan.h"

#include <alloca.h>
#include <string.h>
#include "ch.h"
#include "fc_config.h"
#include "fc_gmap.h"
#include "fc_tempsrc.h"
#include "hal.h"
#include "chdebug.h"
#include "chsystypes.h"

struct FanTachoInfo {
    uint16_t batch_pulses;
    uint16_t last_batch_rpm;
} FAN_TACHO_INFO[FAN_PORT_COUNT];

struct FanControlInfo {
    uint8_t tempsrc;
    uint8_t gmap_pts_count;
    struct GmapPoint gmap_pts[FAN_GMAP_PTS];
} FAN_CONTROL_INFO[FAN_PORT_COUNT];

static virtual_timer_t tacho_timer;
static virtual_timer_t control_timer;

static void fan_init_tacho_info(void) {
    for(int i = FAN_PORT_COUNT; i--;) {
        FAN_TACHO_INFO[i].batch_pulses = 0;
        FAN_TACHO_INFO[i].last_batch_rpm = 0;
    }
}

static void tacho_callback(void *arg) {
    struct FanTachoInfo *tacho_info = arg;
    tacho_info->batch_pulses++;
}

static void fan_init_tacho_interrupts(void) {
    for(int i = FAN_PORT_COUNT; i--;) {
        struct FanPort port = FAN_PORTS[i];
        palSetLineCallback(port.tacho_line, tacho_callback, &FAN_TACHO_INFO[i]);
        palEnableLineEvent(port.tacho_line, PAL_EVENT_MODE_RISING_EDGE);
    }
}

static void tacho_timer_callback(void *arg) {
    for(int i = FAN_PORT_COUNT; i--;) {
        FAN_TACHO_INFO[i].last_batch_rpm =
            (FAN_TACHO_INFO[i].batch_pulses * TACHO_TIMER_PERIOD * 60) / 1000;
        FAN_TACHO_INFO[i].batch_pulses = 0;
    }

    chSysLockFromISR();
    chVTSetI(&tacho_timer,
            TIME_MS2I(TACHO_TIMER_PERIOD),
            tacho_timer_callback, NULL);
    chSysUnlockFromISR();
}

static void fan_start_tacho_timer(void) {
    chVTObjectInit(&tacho_timer);
    chVTSet(&tacho_timer,
            TIME_MS2I(TACHO_TIMER_PERIOD),
            tacho_timer_callback, NULL);
}

static void control_timer_callback(void *arg) {
    for(int i = FAN_PORT_COUNT; i--;) {
        struct FanControlInfo *ctrl_info = &FAN_CONTROL_INFO[i];
        Temp temp = tempsrc_get_temp(ctrl_info->tempsrc);
        uint16_t duty = gmap_y_for_x(
                ctrl_info->gmap_pts, ctrl_info->gmap_pts_count, temp);
        fan_set_duty_cycle(FAN_PORTS[i], duty);
    }

    chSysLockFromISR();
    chVTSetI(&control_timer,
            TIME_MS2I(CONTROL_TIMER_PERIOD),
            control_timer_callback, NULL);
    chSysUnlockFromISR();
};

static void fan_start_control_timer(void) {
    chVTObjectInit(&control_timer);
    chVTSet(&control_timer,
            TIME_MS2I(CONTROL_TIMER_PERIOD),
            control_timer_callback, NULL);
}

static void init_pwm_driver(
        PWMDriver *driver, uint32_t freq, pwmcnt_t period) {
    PWMConfig *cfg = alloca(sizeof(PWMConfig) + sizeof(PWMChannelConfig) * PWM_CHANNELS);
    cfg->frequency = freq,
    cfg->period = period;
    cfg->callback = NULL;
    for(int i = driver->channels; i--;) {
        cfg->channels[i] = (PWMChannelConfig) {
            .mode = PWM_OUTPUT_ACTIVE_HIGH,
            .callback = NULL,
        };
    }
    pwmStart(driver, cfg);
}

static void fan_init_pwm(void) {
    // XXX: There are only 4 timers on the original hardware, may need
    // attention when porting
    PWMDriver *drivers_4pin[4] = { 0, 0, 0, 0 };
    PWMDriver *drivers_3pin[4] = { 0, 0, 0, 0 };

    for(int i = FAN_PORT_COUNT; i--;) {
        struct FanPort port = FAN_PORTS[i];
        _Bool driver_in_arr = FALSE;
        for(int j = 4; j--;) {
            if(drivers_4pin[i] == port.pwm_driver) {
                chDbgAssert(
                        port.is_4_pin,
                        "All fans of a PWM timer need to be the same type");
                driver_in_arr = TRUE;
            }
            if(drivers_3pin[i] == port.pwm_driver) {
                chDbgAssert(
                        !port.is_4_pin,
                        "All fans of a PWM timer need to be the same type");
                driver_in_arr = TRUE;
            }
        }
        if(!driver_in_arr) {
            if(port.is_4_pin) {
                for(int j = 4; j--;) {
                    if(drivers_4pin[j] == NULL) {
                        drivers_4pin[j] = port.pwm_driver;
                        break;
                    }
                }
            } else {
                for(int j = 4; j--; ) {
                    if(drivers_3pin[j] == NULL) {
                        drivers_3pin[j] = port.pwm_driver;
                        break;
                    }
                }
            }
        }
    }

    for(int j = 4; j--;) {
        PWMDriver *driver = drivers_4pin[j];
        if(driver != NULL) {
            init_pwm_driver(driver, FAN_4PIN_PWM_CLOCK, FAN_4PIN_PWM_PERIOD);
        }
    }
    for(int j = 4; j--;) {
        PWMDriver *driver = drivers_3pin[j];
        if(driver != NULL) {
            init_pwm_driver(driver, FAN_3PIN_PWM_CLOCK, FAN_3PIN_PWM_PERIOD);
        }
    }
}

void fan_init_ports(void) {
    fan_init_pwm();
    fan_init_tacho_info();
    fan_init_tacho_interrupts();
    fan_start_tacho_timer();
    fan_start_control_timer();
}

int fan_by_name(char *name) {
    for(int i = FAN_PORT_COUNT; i--;) {
        if(strcmp(name, FAN_PORTS[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void fan_set_duty_cycle(struct FanPort port, uint16_t duty) {
    pwmEnableChannel(
            port.pwm_driver,
            port.pwm_channel - 1,
            PWM_PERCENTAGE_TO_WIDTH(port.pwm_driver, duty));
}

uint16_t fan_get_rpm(int i) {
    return FAN_TACHO_INFO[i].last_batch_rpm;
}

void fan_init_control_blank(void) {
    for(int i = FAN_PORT_COUNT; i--;) {
        FAN_CONTROL_INFO[i].tempsrc = 0;
        FAN_CONTROL_INFO[i].gmap_pts_count = 1;
        FAN_CONTROL_INFO[i].gmap_pts[0].x = 0;
        FAN_CONTROL_INFO[i].gmap_pts[0].y = 0;
    }
}

void fan_set_tempsrc(int i_fan, int i_tempsrc) {
    FAN_CONTROL_INFO[i_fan].tempsrc = i_tempsrc;
}

void fan_set_gmap(
        int i, struct GmapPoint pts[FAN_GMAP_PTS], uint8_t pts_count) {
    FAN_CONTROL_INFO[i].gmap_pts_count = pts_count;
    memcpy(FAN_CONTROL_INFO[i].gmap_pts,
           pts, sizeof(struct GmapPoint) * pts_count);
}

struct GmapPoint *fan_get_gmap(int i) {
    return FAN_CONTROL_INFO[i].gmap_pts;
}

uint8_t fan_get_gmap_pts_count(int i) {
    return FAN_CONTROL_INFO[i].gmap_pts_count;
}
