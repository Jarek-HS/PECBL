#include "int_lib.h" // 為了 COMPILER_RT_ABI
#define DOUBLE_PRECISION
#include "fp_LD_To_posit64_impl.inc"

COMPILER_RT_ABI double LD_to_posit64(long double a) {
  return __Ldouble_to_posit64__(a);
}
