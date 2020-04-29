#pragma once

#include <stdint.h>

_Bool fixedpt_parse(char *str, uint8_t decimal_places, int32_t *out);
void fixedpt_to_str(int32_t val, uint8_t decimal_places, char out[16]);
