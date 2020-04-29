#include "fc_gmap.h"

void gmap_flip(struct GmapPoint pts[], size_t pts_len) {
    for(int i = pts_len; i--;) {
        int32_t tmp = pts[i].x;
        pts[i].x = pts[i].y;
        pts[i].y = tmp;
    }
}
void gmap_sort_pts_by_x(struct GmapPoint pts[], size_t pts_len) {
    // Just simple bubble sort, this is meant for arrays of ~10 items
    _Bool swapped = 0;
    do {
        swapped = 0;
        for(size_t i = 0; i < pts_len - 1; i++) {
            if(pts[i].x > pts[i + 1].x) {
                struct GmapPoint temp = pts[i + 1];
                pts[i + 1] = pts[i];
                pts[i] = temp;
                swapped = 1;
            }
        }
    } while(swapped);
}
int32_t gmap_y_for_x(struct GmapPoint pts[], size_t pts_len, int32_t x) {
    if(x <= pts[0].x) {
        return pts[0].y;
    }
    if(x >= pts[pts_len - 1].x) {
        return pts[pts_len - 1].y;
    }
    for(size_t i = 0; i < pts_len - 1; i++) {
        if(pts[i].x < x && pts[i+1].x > x) {
            int32_t ptdist = pts[i+1].x - pts[i].x;
            int32_t ptydist = pts[i+1].y - pts[i].y;
            int32_t xdist = x - pts[i].x;
            return pts[i].y + (xdist*ptydist)/ptdist;
        }
    }
    return 0; // Should never get here
}
