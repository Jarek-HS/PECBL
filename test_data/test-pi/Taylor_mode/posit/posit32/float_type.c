#include <stdio.h>
#include <math.h>
#include <time.h>

// 計算 arctan(x) 的泰勒級數展開到指定項數
float arctan(float x, int terms) {
    float result = 0.0;
    float power = x;
    for (int i = 0; i < terms; i++) {
        float term = power / (2 * i + 1);
        if (i % 2 == 0)
            result += term;
        else
            result -= term;
        power *= x * x;
    }
    return result;
}

int main() {
    FILE *f_error = fopen("posit64_error.txt", "w");
    FILE *f_time = fopen("posit64_time.txt", "w");
    FILE *f_pi = fopen("posit64_pi.txt", "w");
    if (!f_error || !f_time) {
        perror("fopen failed");
        return 1;
    }

    // 精準圓周率（float 精度可達到的極限）
    float baseline_pi = 3.14159265358979323846264338327950288419716939937510;

    for (int terms = 1; terms <= 20; terms++) {
        clock_t start = clock();  // 開始計時

        float pi = 4.0 * (4.0 * arctan(1.0 / 5.0, terms) - arctan(1.0 / 239.0, terms));

        clock_t end = clock();    // 結束計時
        float time_spent = (float)(end - start) / CLOCKS_PER_SEC;

        // 計算誤差
        float error = fabs(pi - baseline_pi);

        // 寫入檔案
        fprintf(f_pi, "%d %.30f\n", terms, pi);
        fprintf(f_error, "%d %.30f\n", terms, error);
        fprintf(f_time, "%d %.6f\n", terms, time_spent);
    }

    fclose(f_error);
    fclose(f_time);
    fclose(f_pi);
    printf("Completed. Output written to posit64_error.txt and posit64_time.txt\n");
    return 0;
}

//clang  -fposit -g -O3 -march=rv64imac -mabi=lp64  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/" -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include -I/home/jiahua/riscv/riscv-gnu-toolchain/build/lib/gcc/riscv64-unknown-linux-gnu/14.2.0/include/ -static -c  float_type.c -o float_type_mem.o

//clang++ -fposit -g -O3  --gcc-toolchain="/home/jiahua/riscv/riscv-gnu-toolchain/build/"   -march=rv64imac -mabi=lp64   -I/home/jiahua/universal/build/generated -I/home/jiahua/universal/./include  -static  float_type_mem.o -o float_type_mem   -lclang_rt -lposit_c_api_shim 