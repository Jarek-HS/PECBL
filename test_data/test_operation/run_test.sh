#!/bin/bash

# 若有錯誤就中止
set -e

rm -f input.txt
rm -f output_native.txt
rm -f output_posit.txt
echo "Step 1: Generate input"
gcc gen_input.c -o gen_input
./gen_input
echo "✅ input.txt generated"

echo "Step 2: Compile and run native IEEE-754 test"
gcc test_native.c -o test_native
./test_native
echo "✅ Native test complete"

echo "Step 3: Compile and run posit test"
clang  -fposit -march=rv64imac -mabi=lp64  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c  test_posit.c -o test_posit.o
clang++ -fposit   --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/"   -march=rv64imac -mabi=lp64   -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include  -static  test_posit.o -o test_posit   -lclang_rt -lposit_c_api_shim 
./test_posit
echo "✅ Posit test complete"

echo "Step 4: Compare outputs"
python3 compare.py
