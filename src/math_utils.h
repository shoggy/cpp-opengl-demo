#pragma once

#include <algorithm>
#include <cmath>

static inline float clampf(float v, float lo, float hi) {
    return std::max(lo, std::min(hi, v));
}

static inline float lerpf(float a, float b, float t) {
    return a + t * (b - a);
}

static inline bool pointInTriangle(
    float px, float py, float ax, float ay, float bx, float by, float cx, float cy) {
    auto sign = [](float x1, float y1, float x2, float y2, float x3, float y3) -> float {
        return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
    };
    float d1 = sign(px, py, ax, ay, bx, by);
    float d2 = sign(px, py, bx, by, cx, cy);
    float d3 = sign(px, py, cx, cy, ax, ay);
    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(has_neg && has_pos);
}
