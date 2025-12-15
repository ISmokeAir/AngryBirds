#include "Vector2D.h"

Vector2D::Vector2D(double xVal, double yVal) : x(xVal), y(yVal) {
}

Vector2D::Vector2D(const Vector2D& other) : x(other.x), y(other.y) {
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

Vector2D::~Vector2D() {
}

double Vector2D::getX() const {
    return this->x;
}

double Vector2D::getY() const {
    return this->y;
}

void Vector2D::setX(double xVal) {
    this->x = xVal;
}

void Vector2D::setY(double yVal) {
    this->y = yVal;
}

double Vector2D::distanta(const Vector2D& other) const {
    double dx = this->x - other.x;
    double dy = this->y - other.y;
    return std::sqrt((dx * dx) + (dy * dy));
}

double Vector2D::magnitudine() const {
    return std::sqrt((this->x * this->x) + (this->y * this->y));
}

double Vector2D::produsScalar(const Vector2D& other) const {
    return (this->x * other.x) + (this->y * other.y);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(this->x - other.x, this->y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(this->x * scalar, this->y * scalar);
}

bool Vector2D::operator==(const Vector2D& other) const {
    const double epsilon = 0.0001;
    return (std::abs(this->x - other.x) < epsilon) && (std::abs(this->y - other.y) < epsilon);
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}