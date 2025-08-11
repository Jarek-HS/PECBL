# PECBL (Posit Format Extension Compiler Based on LLVM)

PECBL is a compiler extension that integrates the Posit number format into the LLVM framework.

## Installation

### Step 1
Clone the repository:
```sh
git clone https://github.com/Jarek-HS/PECBL.git
```

### Step 2
Create a build directory (all build outputs will be placed here):
```sh
cd PECBL/
mkdir build
```

## Build RISC-V Toolchain
```sh
git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git
cd riscv-gnu-toolchain/
git submodule update --remote
cd ../build/
# Toolchain configuration
../riscv-gnu-toolchain/configure --prefix=$HOME/PECBL/build --enable-linux --enable-multilib --with-arch=rv64imac --with-abi=lp64

make
```

## Build Universal Number Library
```sh
mkdir build_universal

cmake ../universal -DCMAKE_INSTALL_PREFIX:PATH=$HOME/PECBL/build_universal -DBUILD_C_API_SHIM_LIB=ON -DBUILD_DEMONSTRATION=OFF -DCMAKE_C_COMPILER=$HOME/PECBL/build/bin/riscv64-unknown-linux-gnu-gcc -DCMAKE_CXX_COMPILER=$HOME/PECBL/build/bin/riscv64-unknown-linux-gnu-g++ -DCMAKE_C_FLAGS="-march=rv64imac -mabi=lp64 -static -fno-omit-frame-pointer -fno-inline -fkeep-inline-functions -ggdb -gdwarf-4 " -DCMAKE_CXX_FLAGS="-march=rv64imac -mabi=lp64 -static  -fno-omit-frame-pointer -fno-inline -fkeep-inline-functions -ggdb -gdwarf-4"

make
```

## Build Clang/LLVM
```sh
mkdir build_llvm

cmake -G "Ninja" -DLLVM_ENABLE_PROJECTS="clang;lld" -DLLVM_TARGETS_TO_BUILD="RISCV" -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_EH=ON -DLLVM_DEFAULT_TARGET_TRIPLE="riscv64-unknown-linux-gnu" -DCMAKE_BUILD_TYPE=Release -DLLVM_USE_LINKER=gold -DCMAKE_CXX_STANDARD=20 -DCMAKE_INSTALL_PREFIX="$HOME/PECBL/build/" -DDEFAULT_SYSROOT="$HOME/PECBL/build/sysroot" -DCMAKE_C_FLAGS=" -I$HOME/PECBL/build/generated -I$HOME/PECBL/universal/include" -DCMAKE_CXX_FLAGS="-std=c++20 -I$HOME/PECBL/build/generated -I$HOME/PECBL/universal/include" -DCMAKE_POSITION_INDEPENDENT_CODE=ON ../llvm-project/llvm

ninja
```

## Build compiler-rt
```sh
mkdir build_compiler-rt

cmake -G "Ninja" -DCMAKE_C_COMPILER="$HOME/PECBL/build_llvm/bin/clang" -DCMAKE_CXX_COMPILER="$HOME/PECBL/build_llvm/bin/clang++" -DCMAKE_AR="$HOME/PECBL/build_llvm/bin/llvm-ar" -DCMAKE_NM="$HOME/PECBL/build_llvm/bin/llvm-nm" -DCMAKE_RANLIB="$HOME/PECBL/build_llvm/bin/llvm-ranlib" -DCMAKE_OBJDUMP="$HOME/PECBL/build_llvm/bin/llvm-objdump" -DCMAKE_OBJCOPY="$HOME/PECBL/build_llvm/bin/llvm-objcopy" -DCMAKE_STRIP="$HOME/PECBL/build_llvm/bin/llvm-strip" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$HOME/PECBL/build_compiler-rt" -DCOMPILER_RT_BUILD_BUILTINS=ON -DCOMPILER_RT_BUILD_SANITIZERS=OFF -DCOMPILER_RT_BUILD_XRAY=OFF -DCOMPILER_RT_BUILD_PROFILE=OFF -DCOMPILER_RT_BUILD_LIBFUZZER=OFF -DCOMPILER_RT_BUILD_MEMPROF=OFF -DCOMPILER_RT_BUILD_GWP_ASAN=OFF -DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON -DCMAKE_C_COMPILER_TARGET="riscv64-unknown-linux-gnu" -DCMAKE_ASM_COMPILER_TARGET="riscv64-unknown-linux-gnu" -DCMAKE_SYSROOT="$HOME/PECBL/build/sysroot" -DCMAKE_SYSTEM_NAME=Generic -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY -DCOMPILER_RT_BAREMETAL_BUILD=ON -DCMAKE_C_FLAGS=" -march=rv64imac -mabi=lp64 -I../universal/build/generated -I../universal/include --gcc-toolchain=$HOME/PECBL/build/ -Wall -Wpedantic -Wno-narrowing -Wno-deprecated -O3 -DNDEBUG -D REGRESSION_LEVEL_OVERRIDE -D REGRESSION_LEVEL_1=1 -D REGRESSION_LEVEL_2=0 -D REGRESSION_LEVEL_3=0 -D REGRESSION_LEVEL_4=0 $HOME/PECBL/build/c_api/shim/posit/libposit_c_api_shim.a" -DCMAKE_CXX_FLAGS=" -march=rv64imac -mabi=lp64 -I../universal/build/generated -I../universal/include --gcc-toolchain=$HOME/PECBL/build/ -Wall -Wpedantic -Wno-narrowing -Wno-deprecated -O3 -DNDEBUG -D REGRESSION_LEVEL_OVERRIDE -D REGRESSION_LEVEL_1=1 -D REGRESSION_LEVEL_2=0 -D REGRESSION_LEVEL_3=0 -D REGRESSION_LEVEL_4=0 $HOME/PECBL/build_universal/c_api/shim/posit/libposit_c_api_shim.a" -DCMAKE_EXE_LINKER_FLAGS="-L$HOME/PECBL/build/lib" ../llvm-project/compiler-rt

ninja
```

## Copy Required Libraries
After building, because Clang's sysroot structure differs from GCC's, certain libraries must be manually copied into Clang's sysroot. A helper script is provided for this purpose:

```sh
chmod +x ./copylib.sh
./copylib.sh
```

## How to Compile

### Posit Type
Compile with the `-fposit` compiler flag and link with both `libclang_rt.a` and `libposit_c_api_shim.a`.  
Since `libposit_c_api_shim.a` is wrapped in C++ macros, you must use `clang` as the compiler and `clang++` as the linker.

```sh
./build_llvm/bin/clang -fposit -fuse-ld=lld -march=rv64imac -mabi=lp64 -static test.c -c -o test.o
```

```sh
./build_llvm/bin/clang++ -fposit -fuse-ld=lld -march=rv64imac -mabi=lp64 -static test.o -lclang_rt -lposit_c_api_shim
```

### IEEE-754 Type
If you are building for IEEE-754 format only, using Clang as both compiler and linker is sufficient.  
You still need to link with `libclang_rt.a`.

```sh
./build_llvm/bin/clang -fuse-ld=lld -march=rv64imac -mabi=lp64 -static test.c -lclang_rt
```

---

### Note
Currently, only C code is supported for the Posit format.
