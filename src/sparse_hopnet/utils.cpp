#include "utils.hpp"

float   logistic(float x) {
    return 1 / (1 + std::exp(-x));
}

float   clamp(float x, float max) {
    return std::min(1.0f * max, std::max(-1.0f, x * max));
}