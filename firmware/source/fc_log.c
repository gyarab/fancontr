#include "fc_config.h"
#include "hal.h"
#include "chprintf.h"
#include "usbcfg.h"

// Called by the halt hook
void log_halt(char *reason) {
    if(SHELL_PORT == ShellPort_UART) {
        chprintf((BaseSequentialStream *) &SD3, EOL "HALT: %s" EOL, reason);
    } else if(SHELL_PORT == ShellPort_USB) {
        chprintf((BaseSequentialStream *) &SDU1, EOL "HALT: %s" EOL, reason);
    }
}
