#include "marco_struct_def_fucdeclaration.h"
#include <math.h>

// 钳制函数
float clamp(float value, float min, float max) {  //限制值在值域内
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// 线性插值
float lerp(float a, float b, float t) {
    return a + (b - a) * clamp(t, 0.0f, 1.0f);
}

// 反向线性插值
float inverse_lerp(float value, float min, float max) {
    if (max == min) return 0.0f;
    return clamp((value - min) / (max - min), 0.0f, 1.0f);
}

// 回合效用曲线：回合数越小效用越高
float bout_utility(float bout, float optimal_range, float max_range) {
    if (bout <= optimal_range) return 1.0f;
    if (bout >= max_range) return 0.0f;

    // 超出最佳范围后线性下降
    return 1.0f - ((bout - optimal_range) / (max_range - optimal_range));
}