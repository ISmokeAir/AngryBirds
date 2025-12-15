#ifndef OOP_VECTOR2D_H
#define OOP_VECTOR2D_H

#pragma once
#include <cmath>
#include <ostream>

class Vector2D {
private:
    double x, y;

public:

    explicit Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }

    [[nodiscard]] double distanta(const Vector2D& other) const {
        return std::sqrt((x - other.x)*(x - other.x) +
                         (y - other.y)*(y - other.y));
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.getX() << ", " << v.getY() << ")";
        return os;
    }

};

#endif //OOP_VECTOR2D_H