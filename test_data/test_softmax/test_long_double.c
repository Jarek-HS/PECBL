#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <float.h>

#define N 1000
#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 4294967296.0L  // 2^32 as long double

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

// [-1.0, 1.0) 範圍的亂數 long double
long double rand_long_double() {
    uint32_t r = Rand();
    long double normalized = (long double)r / LCG_M;
    return normalized * 20.0L - 10.0L;
}

// softmax 實作（long double precision）
void softmax(const long double *input, long double *output, int length) {
    long double max_val = -LDBL_MAX;
    for (int i = 0; i < length; i++) {
        if (input[i] > max_val) {
            max_val = input[i];
        }
    }

    long double sum = 0.0L;
    for (int i = 0; i < length; i++) {
        output[i] = expl(input[i] - max_val);
        sum += output[i];
    }

    for (int i = 0; i < length; i++) {
        output[i] /= sum;
    }
}

int main() {
    static long double input[N];
    static long double output[N];
    Initrand(42);

    FILE *fp = fopen("softmax_long_double_10.out", "w");
    if (!fp) {
        perror("Failed to open output file");
        return 1;
    }

    // 產生 [-1.0, 1.0) 輸入
    for (int i = 0; i < N; i++) {
        input[i] = rand_long_double();
    }

    // 執行 softmax
    softmax(input, output, N);

    // 輸出
    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.21Lf\n", output[i]);  // 輸出 long double 精度
    }

    fclose(fp);
    return 0;
}
// \
clang -g -O3 -march=rv64imac -mabi=lp64 --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c test_long_double.c -o test_long_double.o\
clang++ -g -O3 --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -march=rv64imac -mabi=lp64 -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -static test_long_double.o -o test_long_double -lclang_rt -lposit_c_api_shim
