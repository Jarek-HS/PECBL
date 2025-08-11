#include <stdio.h>
#include <stdint.h>
#include <limits.h>  // for INT_MAX and INT_MIN

uint64_t double_to_bits(double d) {
    union {
        double d;
        uint64_t u;
    } u;
    u.d = d;
    return u.u;
}

int main() {
    FILE *in = fopen("input.out", "r");
    FILE *out = fopen("compiler64.out", "w");
    if (!in || !out) {
        perror("Failed to open input or output file");
        return 1;
    }

    double a, b;
    int c;

    while (fscanf(in, "%lf %lf %d", &a, &b, &c) == 3) {
    double add = a + b;
    double sub_ab = a - b;
    double mul = a * b;
    double div = a / b;
    double fa = (double)c;
    int cmp_result = (a > b) ? 1 : (a < b) ? -1 : 0;

    fprintf(out,
        "0x%016lX 0x%016lX 0x%016lX 0x%016lX 0x%016lX ",
        double_to_bits(add),
        double_to_bits(sub_ab),
        double_to_bits(mul),
        double_to_bits(div),
        double_to_bits(fa)
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
    printf("Done: all results written to compiler.out\n");
    return 0;
}
//\
clang  -fposit  -O3 -march=rv64imac -mabi=lp64  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c  test_compiler64.c -o test_compiler64.o\
clang++ -fposit   --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/"   -march=rv64imac -mabi=lp64   -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include  -static  test_compiler64.o -o test_compiler64   -lclang_rt -lposit_c_api_shim