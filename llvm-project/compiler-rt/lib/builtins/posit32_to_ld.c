#include "int_lib.h" // 為了 COMPILER_RT_ABI
#define DOUBLE_PRECISION
#include "fp_posit32_To_LD_impl.inc"

COMPILER_RT_ABI long double posit32_to_LD(uint64_t a) {
  return posit32toLD(a);
}
