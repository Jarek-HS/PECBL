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
    FILE *out = fopen("lib.out", "w");
    if (!in || !out) {
        perror("Failed to open input or output file");
        return 1;
    }

    float a1, b1;
    int c;

    while (fscanf(in, "%f %f %d", &a1, &b1, &c) == 3) {
    posit32_t a = posit32_fromd(a1);
    posit32_t b = posit32_fromd(b1);
    posit32_t add = posit32_add(a, b);
    posit32_t sub_ab = posit32_sub(a, b);
    posit32_t mul = posit32_mul(a, b);
    posit32_t div = posit32_div(a, b);
    posit32_t fa = posit32_fromsi(c); 
    fprintf(out,
        "0x%08X 0x%08X 0x%08X 0x%08X 0x%08X ",
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
        fprintf(out, "%d ", posit32_tosi(a));
    }
    fprintf(out, "%d\n", posit32_cmp(a, b));
    }

    fclose(in);
    fclose(out);
    printf("Done: all results written to output.txt\n");
    return 0;
}
//\
g++ -g  -I/home/jiahua/universal/include -L/home/jiahua/universal/build/c_api/shim/posit -L/home/jiahua/universal/build/c_api/shim/posit test_posit.c -o test_posit -lposit_c_api_shim
