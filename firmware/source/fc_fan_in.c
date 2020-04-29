#include "fc_fan_in.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "fc_config.h"
#include "hal_pal.h"

struct FanInPwmInfo {
    char name[10];
    uint16_t high_start_tick;
    uint16_t low_start_tick;
    uint16_t duty_cycles[FAN_IN_PWM_AVG_POINTS];
    uint8_t duty_cycles_i;
    uint16_t duty_cycle_avg;
} FAN_IN_PWM_INFO[FAN_IN_PORT_COUNT];

static virtual_timer_t tacho_timer;

static void tacho_timer_callback(void *arg) {
    for(int i = FAN_IN_PORT_COUNT; i--;) {
        palToggleLine(FAN_IN_PORTS[0].tacho_line);
    }

    chSysLockFromISR();
    chVTSetI(&tacho_timer, TIME_MS2I(20), tacho_timer_callback, NULL);
    chSysUnlockFromISR();
}

static void pwm_callback(void *arg) {
    int i = (int) arg;
    struct FanInPwmInfo *pwm_info = &FAN_IN_PWM_INFO[i];
    if(palReadLine(FAN_IN_PORTS[i].pwm_line) == PAL_LOW) { // Falling edge
        pwm_info->low_start_tick = chVTGetSystemTimeX();
    } else { // Rising edge
        systime_t now = chVTGetSystemTimeX();
        // Guard against timer rollover, we can afford to miss one datapoint
        if(pwm_info->high_start_tick > pwm_info->low_start_tick
           || pwm_info->low_start_tick > now) {
            return;
        }
        pwm_info->duty_cycles[pwm_info->duty_cycles_i] =
            (pwm_info->high_start_tick - pwm_info->low_start_tick * 10000)
            / (now - pwm_info->high_start_tick);
        uint32_t sum = 0;
        for(int j = FAN_IN_PWM_AVG_POINTS; j--;) {
            sum += pwm_info->duty_cycles[j];
        }
        pwm_info->duty_cycle_avg = sum / FAN_IN_PWM_AVG_POINTS;

        pwm_info->high_start_tick = now;
    }
}

void fan_in_init(void) {
    for(int i = FAN_IN_PORT_COUNT; i--;) {
        chsnprintf(FAN_IN_PWM_INFO[i].name, 10, "fan_in_%d", i);
        FAN_IN_PWM_INFO[i].low_start_tick = 0;
        FAN_IN_PWM_INFO[i].high_start_tick = 0;
        FAN_IN_PWM_INFO[i].duty_cycle_avg = 0;
        FAN_IN_PWM_INFO[i].duty_cycles_i = 0;
        for(int j = FAN_IN_PWM_AVG_POINTS; j--;) {
            FAN_IN_PWM_INFO[i].duty_cycles[j] = 0;
        }

        palSetLineCallback(
                FAN_IN_PORTS[i].pwm_line, pwm_callback, (void *) i);
        palEnableLineEvent(FAN_IN_PORTS[i].pwm_line, PAL_EVENT_MODE_BOTH_EDGES);
    }

    chVTObjectInit(&tacho_timer);
    // Currently, all fan in ports will generate a 40ms square wave on the
    // tacho line. This is mostly to stop the computer from worrying that
    // the fans are dead, so the exact value isn't important.
    chVTSet(&tacho_timer, TIME_MS2I(20), tacho_timer_callback, NULL);
}

uint16_t fan_in_get_duty_cycle(int i) {
    return FAN_IN_PWM_INFO[i].duty_cycle_avg;
}

const char *fan_in_get_name(int i) {
    return FAN_IN_PWM_INFO[i].name;
}
