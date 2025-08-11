#include <stdio.h>
#include <math.h>
#include <time.h>


int main() {

    clock_t start = clock();  // 開始計時

    float pi = 4.0 * (4.0 * atan(1.0 / 5.0) - atan(1.0 / 239.0));

    clock_t end = clock();    // 結束計時

    float time_spent = (float)(end - start) / CLOCKS_PER_SEC;

    // 精準圓周率，取前20位
    float baseline_pi = 3.14159265358979323846;

    // 計算誤差
    float error = fabs(pi - baseline_pi);

    // 輸出結果
    printf("π ≈ %.15f\n", pi);
    printf("Baseline π = %.20f\n", baseline_pi);
    printf("誤差值 = %.20f\n", error);
    printf("執行時間：%.6f 秒\n", time_spent);

    return 0;
}
