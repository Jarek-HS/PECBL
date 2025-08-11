#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
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

float rand_float() {
    uint32_t r = Rand();
    float normalized = (float)r / LCG_M;
    return  normalized * 20.0f - 10.0f;
}
void softmax(const float *input, float *output, int length) {
    float max_val = -FLT_MAX;
    for (int i = 0; i < length; i++) {
        if (input[i] > max_val) {
            max_val = input[i];
        }
    }

    float sum = 0.0f;
    for (int i = 0; i < length; i++) {
        output[i] = expf(input[i] - max_val);
        sum += output[i];
    }

    for (int i = 0; i < length; i++) {
        output[i] /= sum;
    }
}

int main() {
    static float input[N];
    static float output[N];
    Initrand(42);

    FILE *fp = fopen("softmax_posit32_10.out", "w");
    if (!fp) {
        perror("Failed to open output file");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        input[i] = rand_float();
    }

    softmax(input, output, N);

    // 將所有 softmax 輸出寫入檔案
    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.10f\n", output[i]);
    }

    fclose(fp);

    return 0;
}
// \
clang -fposit -g -O3 -march=rv64imac -mabi=lp64  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c  test_posit32.c -o test_posit32.o \
clang++ -fposit -g -O3  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/"   -march=rv64imac -mabi=lp64   -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include  -static  test_posit32.o -o test_posit32   -lclang_rt -lposit_c_api_shim