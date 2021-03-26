#ifndef HEADER_SHAMIR
#define HEADER_SHAMIR

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct _shamir {
    uint32_t key_number; // k
    int64_t secret; // Data
    double* table; // table with element
    uint32_t tab_size; // Size of tab
} shamir;

shamir* sh_create(uint16_t k,int64_t secret);
void sh_destroy(shamir* s);
double sh_compute_x(shamir* s, uint32_t x);
void sh_print(shamir* s);
double _sh_greater_random(int64_t value);
double sh_evaluate(uint32_t k,char** points,uint32_t points_number);

#endif
