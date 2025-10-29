//
// Created by matei on 10/28/2025.
//

#ifndef OOP_VECTOR2D_H
#define OOP_VECTOR2D_H

#pragma once
#include <cmath>   // necesar pentru sqrt()
#include <ostream>

class Vector2D {
private:
    double x, y;

public:
    // Constructor explicit: evită conversii implicite gen Vector2D v = 5;
    explicit Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }

    [[nodiscard]] double distanta(const Vector2D& other) const {
        return std::sqrt((x - other.x)*(x - other.x) +
                         (y - other.y)*(y - other.y));
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

#endif //OOP_VECTOR2D_H