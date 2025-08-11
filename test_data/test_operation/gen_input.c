#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <limits.h>

static uint32_t seed = 74755;
#define LCG_A 1664525
#define LCG_C 1013904223

void Initrand(uint32_t s) {
    if (s == 0) s = 1;
    seed = s;
}

uint32_t Rand() {
    seed = LCG_A * seed + LCG_C;
    return seed;
}

// 產生範圍為 [-FLT_MAX, +FLT_MAX] 的 float，避開 NaN 和 Inf
float RandFloatFullRange() {
    union {
        uint32_t u;
        float f;
    } u;

    do {
        u.u = Rand();
    } while (isnan(u.f) || isinf(u.f));  // 排除 NaN 和無限大

    return u.f;
}

// 產生整個 int 範圍的亂數：INT_MIN 到 INT_MAX
int RandIntFullRange() {
    uint32_t hi = Rand();
    uint32_t lo = Rand();
    uint32_t combined = (hi << 16) | (lo & 0xFFFF);
    return (int)combined;
}

int main() {
    FILE *fp = fopen("input.out", "w");
    if (!fp) {
        perror("Failed to open output file");
        return 1;
    }

    Initrand(74755);

    for (int i = 0; i < 1000000; i++) {
        float a = RandFloatFullRange();
        float b = RandFloatFullRange();
        int c = RandIntFullRange();

        // 使用 %.10e 可顯示完整 float 範圍（包括非常大/小的數）
        fprintf(fp, "%.10e %.10e %d\n", a, b, c);
    }

    fclose(fp);
    return 0;
}
