#include "llvm/Support/PositSemantics.h"

namespace llvm {
  // Define the use_posit command-line option with a default value of false
  cl::opt<bool> use_posit("use-posit", cl::desc("Enable posit floating-point semantics"), cl::init(false));
}
