
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../../../universal/include/universal/number/posit/posit_c_api.h"

static inline long double posit32toLD(uint32_t d) {
    
    uint32_t pa = *(uint32_t *)&d;
    posit32_t pa1 = posit32_reinterpret(pa);
    long double ld = posit32_told(pa1);
    return ld;
}