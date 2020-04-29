/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

#include "fc_shell.h"
#include "fc_fan.h"
#include "fc_fan_in.h"
#include "fc_tempsrc.h"

/*
 * Blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static __attribute__((noreturn)) THD_FUNCTION(Thread1, arg) {

    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
        systime_t time = 500;
        palClearPad(GPIOB, GPIOB_LED);
        chThdSleepMilliseconds(time);
        palSetPad(GPIOB, GPIOB_LED);
        chThdSleepMilliseconds(time);
    }
}

/*
 * Application entry point.
 */
int main(void) {

    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    /*
     * Creates the blinker thread.
     */
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    fan_init_ports();
    // TODO: Save/load profiles
    fan_init_control_blank();
    fan_in_init();
    tempsrc_virt_init();
    setup_shell();
}
