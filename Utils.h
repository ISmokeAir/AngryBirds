#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

namespace Utils {
    template <typename T>
    T clamp(T val, T min, T max) {
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    template <typename T>
    T square(T x) {
        return x * x;
    }

    template <typename T>
    T kineticEnergy(T mass, T velocity) {
        return 0.5 * mass * (velocity * velocity);
    }

    inline void logDebug(const std::string&) {
    }
}

#endif