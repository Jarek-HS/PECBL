
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../../../universal/include/universal/number/posit/posit_c_api.h"

static inline long double posit64toLD(uint64_t d) {
    
    uint64_t pa = *(uint64_t *)&d;
    posit64_t pa1 = posit64_reinterpret(pa);
    long double ld = posit64_told(pa1);
    return ld;
}