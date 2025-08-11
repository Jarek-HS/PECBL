#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>  // for INT_MAX and INT_MIN
#include <float.h>

uint32_t float_to_bits(float f) {
    union {
        float f;
        uint32_t u;
    } u;
    u.f = f;
    return u.u;
}

int main() {
    FILE *in = fopen("input.out", "r");
    FILE *out = fopen("compiler.out", "w");
    if (!in || !out) {
        perror("Failed to open input or output file");
        return 1;
    }

    float a, b;
    int c;


while (fscanf(in, "%f %f %d", &a, &b, &c) == 3) {
    float add = a + b;
    float sub_ab = a - b;
    float mul = a * b;
    float div = a / b;
    float fa = (float)c;
    int cmp_result = (a > b) ? 1 : (a < b) ? -1 : 0;

    fprintf(out,
        "0x%08X 0x%08X 0x%08X 0x%08X 0x%08X ",
        float_to_bits(add),
        float_to_bits(sub_ab),
        float_to_bits(mul),
        float_to_bits(div),
        float_to_bits(fa)
    );

    // 檢查 float 是否在 int 可安全轉換範圍內
    if (a > INT_MAX || a < INT_MIN ) {
        fprintf(out, "ovf ");
    } else {
        fprintf(out, "%d ", (int)a);
    }

    fprintf(out, "%d\n", cmp_result);
}


    fclose(in);
    fclose(out);
    printf("Done: all results written to output.txt\n");
    return 0;
}
// \
clang  -fposit -g -O3 -march=rv64imac -mabi=lp64  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c  test_compiler.c -o test_compiler.o\
clang++ -fposit   --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/"   -march=rv64imac -mabi=lp64   -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include  -static  test_compiler.o -o test_compiler   -lclang_rt -lposit_c_api_shim 