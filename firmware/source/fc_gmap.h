#pragma once

#include <stddef.h>
#include <stdint.h>

struct GmapPoint {
    int32_t x;
    int32_t y;
};

/** Flips x and y */
void gmap_flip(struct GmapPoint pts[], size_t pts_len);
void gmap_sort_pts_by_x(struct GmapPoint pts[], size_t pts_len);
/** Operates on an array of GmapPoints sorted by *x* */
int32_t gmap_y_for_x(struct GmapPoint pts[], size_t pts_len, int32_t x);
