#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#define N 1000
#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 4294967296.0  // 2^32 as double

static uint32_t seed = 42;
// 初始化亂數種子
void Initrand(uint32_t s) {
    if (s == 0) s = 1;
    seed = s;
}

// LCG 產生器
uint32_t Rand() {
    seed = LCG_A * seed + LCG_C;
    return seed;
}

double rand_double() {
    uint32_t r = Rand();
    float normalized = (float)r / LCG_M;
    return normalized * 20.0 - 10.0;
}
// softmax 實作（double precision）
void softmax(const double *input, double *output, int length) {
    double max_val = -DBL_MAX;
    for (int i = 0; i < length; i++) {
        if (input[i] > max_val) {
            max_val = input[i];
        }
    }

    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        output[i] = exp(input[i] - max_val);
        sum += output[i];
    }

    for (int i = 0; i < length; i++) {
        output[i] /= sum;
    }
}

int main() {
    static double input[N];
    static double output[N];
    Initrand(42);

    FILE *fp = fopen("softmax_double_10.out", "w");
    if (!fp) {
        perror("Failed to open output file");
        return 1;
    }

    // 產生亂數輸入 [-1.0, 1.0]
    for (int i = 0; i < N; i++) {
        input[i] = rand_double();
    }

    // 套用 softmax
    softmax(input, output, N);

    // 輸出到 compiler.out 檔案
    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.17lf\n", output[i]);  // double 精度
    }

    fclose(fp);
    return 0;
}
// \
clang  -g -O3 -march=rv64imac -mabi=lp64  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c  test_double.c -o test_double.o \
clang++  -g -O3  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/"   -march=rv64imac -mabi=lp64   -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include  -static  test_double.o -o test_double   -lclang_rt 