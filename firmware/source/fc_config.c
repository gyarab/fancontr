#include "fc_config.h"

struct FanPort FAN_PORTS[] = {
    {
        .name = "1",
        .is_4_pin = TRUE,
        .pwm_line = PAL_LINE(GPIOA, 0),
        .tacho_line = PAL_LINE(GPIOA, 5),
        .pwm_driver = &PWMD2,
        .pwm_channel = 1,
    },
    {
        .name = "2",
        .is_4_pin = TRUE,
        .pwm_line = PAL_LINE(GPIOA, 3),
        .tacho_line = PAL_LINE(GPIOA, 4),
        .pwm_driver = &PWMD2,
        .pwm_channel = 4,
    },
    {
        .name = "3",
        .is_4_pin = TRUE,
        .pwm_line = PAL_LINE(GPIOA, 1),
        .tacho_line = PAL_LINE(GPIOA, 6),
        .pwm_driver = &PWMD2,
        .pwm_channel = 2,
    },
    {
        .name = "4",
        .is_4_pin = TRUE,
        .pwm_line = PAL_LINE(GPIOA, 2),
        .tacho_line = PAL_LINE(GPIOA, 8),
        .pwm_driver = &PWMD2,
        .pwm_channel = 3,
    },
    {
        .name = "5",
        .is_4_pin = TRUE,
        .pwm_line = PAL_LINE(GPIOB, 13),
        .tacho_line = PAL_LINE(GPIOB, 12),
        .pwm_driver = &PWMD1,
        .pwm_channel = 1,
    },
    {
        .name = "6",
        .is_4_pin = FALSE,
        .pwm_line = PAL_LINE(GPIOB, 9),
        .tacho_line = PAL_LINE(GPIOA, 10),
        .pwm_driver = &PWMD4,
        .pwm_channel = 4,
    },
    {
        .name = "7",
        .is_4_pin = FALSE,
        .pwm_line = PAL_LINE(GPIOB, 8),
        .tacho_line = PAL_LINE(GPIOC, 13),
        .pwm_driver = &PWMD4,
        .pwm_channel = 3,
    },
    {
        .name = "8",
        .is_4_pin = FALSE,
        .pwm_line = PAL_LINE(GPIOB, 6),
        .tacho_line = PAL_LINE(GPIOB, 7),
        .pwm_driver = &PWMD4,
        .pwm_channel = 1,
    },
    {
        .name = "9",
        .is_4_pin = FALSE,
        .pwm_line = PAL_LINE(GPIOB, 4),
        .tacho_line = PAL_LINE(GPIOC, 14),
        .pwm_driver = &PWMD3,
        .pwm_channel = 1,
    },
    {
        .name = "10",
        .is_4_pin = FALSE,
        .pwm_line = PAL_LINE(GPIOB, 5),
        .tacho_line = PAL_LINE(GPIOC, 15),
        .pwm_driver = &PWMD3,
        .pwm_channel = 2,
    },
    {
        .name = "11",
        .is_4_pin = FALSE,
        .pwm_line = PAL_LINE(GPIOB, 0),
        .tacho_line = PAL_LINE(GPIOB, 1),
        .pwm_driver = &PWMD3,
        .pwm_channel = 3,
    },
};

struct FanInPort FAN_IN_PORTS[] = {
    /*{
        .name = "fan-in",
        .pwm_line = PAL_LINE(GPIOB, 15),
        .tacho_line = PAL_LINE(GPIOB, 14),
    }*/
};
