#include "fc_util.h"

#include <string.h>
#include <stdlib.h>
#include "hal.h"
#include "chprintf.h"

static int32_t ipow(int32_t b, int32_t n) {
    int32_t res = 1;
    for(int i = n; i--;) { 
        res *= b;
    }
    return res;
}

_Bool fixedpt_parse(char *str, uint8_t decimal_places, int32_t *out) {
    char *point = strchr(str, '.');
    char *end = str + strlen(str);
    int declen;
    if(point == NULL) {
        declen = 0;
    } else {
        declen = end - point - 1;
    }
    char *numend;
    int32_t intpt = strtol(str, &numend, 10);
    if(*numend != '\0' && *numend != '.') {
        return 0;
    }
    int32_t decpt = 0;
    if(point != NULL) {
        decpt = strtol(point + 1, &numend, 10);
        if(numend != end) {
            return 0;
        }
    }
    if(str[0] == '-') {
        decpt *= -1;
    }
    if(declen > decimal_places) {
        decpt /= ipow(10, declen - decimal_places);
    } else if(declen < decimal_places) {
        decpt *= ipow(10, decimal_places - declen);
    }
    *out = (intpt * ipow(10, decimal_places)) + decpt;
    return 1;
}

void fixedpt_to_str(int32_t val, uint8_t decimal_places, char out[16]) {
    char *sign = val < 0 ? "-" : "";
    int32_t intpt = abs(val / ipow(10, decimal_places));
    int32_t decpt = abs(val - (intpt * ipow(10, decimal_places)));
    char fmtstr[16];
    chsnprintf(fmtstr, 16, "%%s%%d.%%0%dd", decimal_places);
    chsnprintf(out, 16, fmtstr, sign, intpt, decpt);
}
