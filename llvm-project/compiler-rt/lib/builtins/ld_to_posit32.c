#include "int_lib.h" // 為了 COMPILER_RT_ABI

#include "fp_LD_To_posit32_impl.inc"

COMPILER_RT_ABI float LD_to_posit32(long double a) {
  return __Ldouble_to_posit32__(a);
}
