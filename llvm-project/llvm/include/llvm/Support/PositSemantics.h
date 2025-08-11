#ifndef LLVM_SUPPORT_POSITSEMANTICS_H
#define LLVM_SUPPORT_POSITSEMANTICS_H

#include "llvm/Support/CommandLine.h"

namespace llvm {
  // Declare the use_posit option using cl::opt
  extern cl::opt<bool> use_posit;
}

#endif // LLVM_SUPPORT_POSITSEMANTICS_H
