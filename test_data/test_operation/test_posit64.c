#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include <limits.h>  // for INT_MAX and INT_MIN
#include "../../../universal/include/universal/number/posit/posit_c_api.h"
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
    FILE *out = fopen("lib64.out", "w");
    if (!in || !out) {
        perror("Failed to open input or output file");
        return 1;
    }

    double a1, b1;
    int c;

    while (fscanf(in, "%lf %lf %d", &a1, &b1, &c) == 3) {
    posit64_t a = posit64_fromd(a1);
    posit64_t b = posit64_fromd(b1);
    posit64_t add = posit64_add(a, b);
    posit64_t sub_ab = posit64_sub(a, b);
    posit64_t mul = posit64_mul(a, b);
    posit64_t div = posit64_div(a, b);
    posit64_t fa = posit64_fromd((double)c); 
    fprintf(out,
        "0x%016lX 0x%016lX 0x%016lX 0x%016lX 0x%016lX ",
        add.v,
        sub_ab.v,
        mul.v,
        div.v,
        fa.v
    );
    // 檢查 float 是否在 int 可安全轉換範圍內
    if (a1 >= INT_MAX || a1 <= INT_MIN ) {
        fprintf(out, "ovf ");
    } else {
        fprintf(out, "%d ", posit64_tosi(a));
    }
    fprintf(out, "%d\n", posit64_cmp(a, b));
    }

    fclose(in);
    fclose(out);
    printf("Done: all results written to output.txt\n");
    return 0;
}
//\
g++ -O3 -I/home/jiahua/universal/include -L/home/jiahua/universal/build/c_api/shim/posit -L/home/jiahua/universal/build/c_api/shim/posit test_posit64.c -o test_posit64 -lposit_c_api_shim
