#!/bin/bash

SRC="$HOME/PECBL/build/lib/gcc/riscv64-unknown-linux-gnu/15.1.0/lib64/lp64"
SRC_SHIM="$HOME/PECBL/build_universal/c_api/shim/posit"
SRC_RT="$HOME/PECBL/build_compiler-rt/lib/generic"
DST="$HOME/PECBL/build/sysroot/lib64/lp64"

mkdir -p "$DST"

cp "$SRC/crtbeginT.o" "$DST/"
cp "$SRC/libgcc.a" "$DST/"
cp "$SRC/libgcc_eh.a" "$DST/"
cp "$SRC_RT/libclang_rt.builtins-riscv64.a" "$DST/libclang_rt.a"
cp "$SRC_SHIM/libposit_c_api_shim.a" "$DST"
echo "copy file to $DST"
