#include "Vector3d.h"
#include <cmath>

using namespace core;

Vector3d::Vector3d() {
    x = y = z = 0;
}

Vector3d::Vector3d(const Vector3d& orig) {
    x = orig.x;
    y = orig.y;
    z = orig.z;
}

Vector3d::Vector3d(float _x, float _y, float _z) {
    x = _x;
    z = _z;
    y = _y;
};

Vector3d::~Vector3d() {
}

bool Vector3d::operator==(const Vector3d& orig)const {
    return (x == orig.x) && (y == orig.y) && (z == orig.z);
}

bool Vector3d::operator!=(const Vector3d &A) {
    return (A.x != x ||
            A.y != y ||
            A.z != z);
};
// Multiply

float Vector3d::operator*(const Vector3d &B) {
    return x * B.x + y * B.y + z * B.z;
};

Vector3d Vector3d::operator ^ (const float C) {
    return Vector3d(x*C, y*C, z * C);
};

Vector3d Vector3d::operator/(const float C) {
    return Vector3d(x / C, y / C, z / C);
};

void Vector3d::operator*=(float C) {
    x *= C;
    y *= C;
    z *= C;
};

// Add

Vector3d Vector3d::operator+(const Vector3d &A) {
    return Vector3d(x + A.x, y + A.y, z + A.z);
};

void Vector3d::operator+=(const Vector3d &A) {
    x += A.x;
    y += A.y;
    z += A.z;
};
// Subtract

Vector3d Vector3d::operator-(const Vector3d &A) {
    return Vector3d(x - A.x, y - A.y, z - A.z);
};

void Vector3d::operator-=(const Vector3d &A) {
    x -= A.x;
    y -= A.y;
    z -= A.z;
};


float Vector3d::Length() {
    return sqrt(x * x + y * y + z * z);
}

void Vector3d::Normalise() {
    auto len = this->Length();
    x = x / len;
    y = y / len;
    z = z / len;
}