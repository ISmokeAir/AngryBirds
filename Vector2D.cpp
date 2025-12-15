#ifndef OOP_VECTOR2D_H
#define OOP_VECTOR2D_H

#pragma once
#include <cmath>
#include <ostream>

class Vector2D {
private:
    double x;
    double y;

public:
    explicit Vector2D(double xVal = 0, double yVal = 0);

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;

    [[nodiscard]] double distanta(const Vector2D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};

#endif