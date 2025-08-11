#include "../../../universal/include/universal/number/posit/posit_c_api.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static inline double __Ldouble_to_posit64__(long double ld) {
    uint64_t uiZ = 0;
    uint64_t mask = 0x8000000000000000;
    uint64_t store [2];
    long double x = ld;
    memcpy(store, &ld, sizeof(long double));
    uint64_t upper = store[1];
    uint64_t lower = store[0];
    if(upper == 0 && lower == 0) return 0; // Zero case
    uint64_t sign = (upper & mask);
    int64_t scale = ((upper >> 48) & 0x7FFF) - 16383; 
    uint64_t fraction = (upper << 16) | (lower >> 48); // Shift to get fraction
    int kA = scale / 4;
    int expA = scale % 4;
    if (scale < 0) {
        expA = 4 + expA;
    }
    uint64_t regime;
    int regime_bits = 0;
    if (scale < 0) {
        regime = 1;
        regime_bits = (-1 * kA) + 1;
    } else {
        regime = 0xFFFFFFFFFFFFFFFF;
        regime_bits = kA + 1;
        regime = regime << 1;
    }
    uint64_t posit = 0, exponent = 0;
    uint64_t fraction_loss =0;
    bool rounding = false;
    exponent = expA;
    int regime_shift;
    regime_shift = (63 - regime_bits);
    regime = (regime << regime_shift);
    regime = (regime >> 1);
    posit = (posit | regime);
    exponent = (exponent << (regime_shift - 3));
    posit = (posit | exponent);
    fraction_loss = (fraction << (64-((64 - regime_shift) + 3)));
    if (fraction_loss >= 0x0100000000000000) rounding = true;
    fraction = (fraction >> ((64 - regime_shift) + 3));
    posit = (posit | fraction);
    if (rounding) posit++;
    if (sign == mask) posit = ~posit;
    double tmp;
    memcpy(&tmp, &posit, sizeof(double));
    return tmp;
}
