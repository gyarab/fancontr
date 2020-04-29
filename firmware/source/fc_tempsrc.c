#include "fc_tempsrc.h"

#include <string.h>
#include <stdlib.h>
#include "hal.h"
#include "chprintf.h"
#include "fc_config.h"
#include "fc_fan_in.h"

struct TempsrcVirtData {
    char name[10];
    Temp value;
} TEMPSRC_VIRT_DATA[TEMPSRC_VIRT_COUNT];

Temp tempsrc_get_temp(int num) {
    if(num < FAN_IN_PORT_COUNT) {
        // TODO
        return 0;
    }
    return TEMPSRC_VIRT_DATA[num - FAN_IN_PORT_COUNT].value;
}
const char *tempsrc_get_name(int num) {
    if(num < FAN_IN_PORT_COUNT) {
        return fan_in_get_name(num);
    }
    return TEMPSRC_VIRT_DATA[num - FAN_IN_PORT_COUNT].name;
}
int tempsrc_by_name(char *name) {
    for(int i = FAN_IN_PORT_COUNT; i--;) {
        if(strcmp(name, fan_in_get_name(i)) == 0) {
            return i;
        }
    }
    for(int i = TEMPSRC_VIRT_COUNT; i--;) {
        if(strcmp(name, TEMPSRC_VIRT_DATA[i].name) == 0) {
            return i + FAN_IN_PORT_COUNT;
        }
    }
    return -1;
}

void tempsrc_virt_init(void) {
    for(int i = TEMPSRC_VIRT_COUNT; i--;) {
        chsnprintf(TEMPSRC_VIRT_DATA[i].name, 10, "virt_%d", i);
        TEMPSRC_VIRT_DATA[i].value = 0;
    }
}

void tempsrc_virt_set_temp(int num, Temp temp) {
    int i = num - FAN_IN_PORT_COUNT;
    TEMPSRC_VIRT_DATA[i].value = temp;
}

_Bool tempsrc_is_virt(int num) {
    return num >= FAN_IN_PORT_COUNT && num < TEMPSRC_COUNT;
}
