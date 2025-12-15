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
    explicit Vector2D(double xVal = 0.0, double yVal = 0.0);
    Vector2D(const Vector2D& other);
    Vector2D& operator=(const Vector2D& other);
    ~Vector2D();

    double getX() const;
    double getY() const;
    void setX(double xVal);
    void setY(double yVal);

    double distanta(const Vector2D& other) const;
    double magnitudine() const;
    double produsScalar(const Vector2D& other) const;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(double scalar) const;

    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};

#endif