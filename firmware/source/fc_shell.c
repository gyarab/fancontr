#include "fc_shell.h"

#include <string.h>
#include <stdlib.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "shell.h"

#include "usbcfg.h"
#include "fc_config.h"
#include "fc_fan.h"
#include "fc_idif.h"
#include "fc_gmap.h"
#include "fc_tempsrc.h"
#include "fc_util.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

static _Bool parse_gmap(
        char *argv[], uint8_t x_dp, uint8_t y_dp, int pts_len,
        struct GmapPoint pts[]) {
    for(int i = 0; i < pts_len; i++) {
        if(!fixedpt_parse(argv[i*2], x_dp, &pts[i].x)
           || !fixedpt_parse(argv[i*2 + 1], y_dp, &pts[i].y)) {
            return 0;
        }
    }
    gmap_sort_pts_by_x(pts, pts_len);
    return 1;
}

static void print_gmap(
        BaseSequentialStream *chp, uint8_t x_dp, uint8_t y_dp, int pts_len,
        struct GmapPoint pts[]) {
    for(int i = 0; i < pts_len; i++) {
        char xstr[16];
        fixedpt_to_str(pts[i].x, x_dp, xstr);
        char ystr[16];
        fixedpt_to_str(pts[i].y, y_dp, ystr);
        chprintf(chp,
                "- x: %s" EOL
                "  y: %s" EOL,
                xstr, ystr);
    }
}

static void cmd_fan_list(BaseSequentialStream *chp, int argc, char *argv[]) {
    for(size_t i = 0; i < FAN_PORT_COUNT; i++) {
        struct FanPort fan = FAN_PORTS[i];
        chprintf(chp,
                "- name: %s" EOL
                "  is 4 pin: %s" EOL
                "  rpm: %d" EOL,
                fan.name, fan.is_4_pin ? "yes" : "no", fan_get_rpm(i));
    }
}

static void cmd_fan_set_tempsrc(
        BaseSequentialStream *chp, int argc, char *argv[]) {
    if(argc != 2) {
        chprintf(chp, "Usage: <fan name> <tempsrc name>" EOL);
        return;
    }
    int fan = fan_by_name(argv[0]);
    if(fan < 0) {
        chprintf(chp, "error: no such fan" EOL);
        return;
    }
    int tempsrc = tempsrc_by_name(argv[1]);
    if(tempsrc < 0) {
        chprintf(chp, "error: no such tempsrc" EOL);
        return;
    }
    fan_set_tempsrc(fan, tempsrc);
}

static void cmd_fan_set_gmap(
        BaseSequentialStream *chp, int argc, char *argv[]) {
    if(argc < 3 || argc > 21 || argc % 2 != 1) {
        // TODO: Change to RPM!
        chprintf(chp,
                "Usage: <fan name> (<temperature> <fan duty>){1,%d}" EOL,
                FAN_GMAP_PTS);
    }
    int fan = fan_by_name(argv[0]);
    if(fan < 0) {
        chprintf(chp, "error: no such fan" EOL);
        return;
    }
    struct GmapPoint pts[FAN_GMAP_PTS];
    if(!parse_gmap(argv + 1, TEMP_DECIMAL_PLACES, DUTY_CYCLE_DECIMAL_PLACES,
                   (argc - 1)/2, pts)) {
        chprintf(chp, "error: invalid gmap" EOL);
        return;
    }
    fan_set_gmap(fan, pts, (argc - 1)/2);
}

static void cmd_fan_get_gmap(
        BaseSequentialStream *chp, int argc, char *argv[]) {
    if(argc != 1) {
        chprintf(chp, "Usage: <fan name>" EOL);
    }
    int fan = fan_by_name(argv[0]);
    if(fan < 0) {
        chprintf(chp, "error: no such fan" EOL);
        return;
    }
    print_gmap(chp, TEMP_DECIMAL_PLACES, 0,
            fan_get_gmap_pts_count(fan),
            fan_get_gmap(fan));
}

static void cmd_tempsrc_list(
        BaseSequentialStream *chp, int argc, char *argv[]) {
    for(size_t i = 0; i < TEMPSRC_COUNT; i++) {
        char temp[16];
        fixedpt_to_str(tempsrc_get_temp(i), TEMP_DECIMAL_PLACES, temp);
        chprintf(chp,
                "- name: %s" EOL
                "  temp: %s" EOL,
                tempsrc_get_name(i), temp);
    }
}

static void cmd_tempsrc_virt_set(
        BaseSequentialStream *chp, int argc, char *argv[]) {
    if(argc != 2) {
        chprintf(chp, "Usage: <tempsrc name> <value>" EOL);
        return;
    }
    int i = tempsrc_by_name(argv[0]);
    if(!tempsrc_is_virt(i)) {
        chprintf(chp, "error: no such virtual tempsrc" EOL);
        return;
    }
    Temp val;
    if(!fixedpt_parse(argv[1], TEMP_DECIMAL_PLACES, &val)) {
        chprintf(chp, "error: invalid value (not a float)" EOL);
        return;
    }
    tempsrc_virt_set_temp(i, val);
}

const ShellCommand commands[] = {
    { "fan_list", cmd_fan_list },
    { "fan_set_tempsrc", cmd_fan_set_tempsrc },
    { "fan_set_gmap", cmd_fan_set_gmap },
    { "fan_get_gmap", cmd_fan_get_gmap },
    { "tempsrc_list", cmd_tempsrc_list },
    { "tempsrc_virt_set", cmd_tempsrc_virt_set },
    { NULL, NULL },
};

void setup_shell(void) {
    if(SHELL_PORT == ShellPort_USB) {
        /*
         * Initializes a serial-over-USB CDC driver.
         */
        sduObjectInit(&SDU1);
        sduStart(&SDU1, &serusbcfg);

        /*
         * Activates the USB driver and then the USB bus pull-up on D+.
         * Note, a delay is inserted in order to not have to disconnect the cable
         * after a reset.
         */
        usbDisconnectBus(serusbcfg.usbp);
        chThdSleepMilliseconds(1500);
        usbStart(serusbcfg.usbp, &usbcfg);
        usbConnectBus(serusbcfg.usbp);

        ShellConfig shell_cfg = {
            .sc_channel = (BaseSequentialStream *) &SDU1,
            .sc_commands = commands,
        };
        shellInit();

        while (true) {
            if (SDU1.config->usbp->state == USB_ACTIVE) {
                thread_t *shell_thd = chThdCreateFromHeap(
                        NULL, SHELL_WA_SIZE, "shell", NORMALPRIO + 1,
                        shellThread, (void *)&shell_cfg);
                chThdWait(shell_thd); /* Waiting termination. */
            }
            chThdSleepMilliseconds(1000);
        }

    } else if(SHELL_PORT == ShellPort_UART) {
        usbDisconnectBus(serusbcfg.usbp);

        SerialConfig serial_config = {
            .speed = 115200,
            .cr1 = 0,
            .cr2 = USART_CR2_STOP1_BITS,
            .cr3 = 0,
        };
        sdStart(&SD3, &serial_config);

        ShellConfig shell_cfg = {
            .sc_channel = (BaseSequentialStream *) &SD3,
            .sc_commands = commands,
        };
        shellInit();

        thread_t *shell_thd = chThdCreateFromHeap(
                NULL, SHELL_WA_SIZE, "shell", NORMALPRIO + 1,
                shellThread, (void *) &shell_cfg);
        chThdWait(shell_thd);
    } else chDbgAssert(false, "Invalid shell port");
}
