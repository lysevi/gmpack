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

float InvSqrt(const float x) {
    union {
        float f;
        int i;
    } t;
    float y;

    t.f = x;
    t.i = 0x5f3759df - (t.i >> 1);
    y = t.f;
    y = y * (1.5F - (0.5F * x * y * y));

    return y;
}

float vw_sqrtf(float x) {
    return x * InvSqrt(x);
}

float Vector3d::Length() {
    return vw_sqrtf(x * x + y * y + z * z);
}

void Vector3d::Normalise() {
    float L_squared, one_over_L;
    L_squared = (x * x) + (y * y) + (z * z);
    one_over_L = InvSqrt(L_squared);
    x = x * one_over_L;
    y = y * one_over_L;
    z = z * one_over_L;
}

const float p180 = 0.0174532925f;

void Vector3d::RotatePoint(Vector3d *Point,const Vector3d& Angle) {
    float xTMP = Point->x;
    float yTMP = Point->y;
    float zTMP = Point->z;

    // X
    if (Angle.x != 0) {
        float a = -Angle.x*p180;
        float c = cos(a);
        float s = sin(a);
        Point->y = yTMP * c + zTMP*s;
        Point->z = -yTMP * s + zTMP*c;
        xTMP = Point->x;
        yTMP = Point->y;
        zTMP = Point->z;
    }

    // Y
    if (Angle.y != 0) {
        float a = Angle.y*p180;
        float c = cos(a);
        float s = sin(a);
        Point->x = xTMP * c + zTMP*s;
        Point->z = -xTMP * s + zTMP*c;
        xTMP = Point->x;
        yTMP = Point->y;
    }

    // Z
    if (Angle.z != 0) {
        float a = -Angle.z*p180;
        float c = cos(a);
        float s = sin(a);
        Point->x = xTMP * c + yTMP*s;
        Point->y = -xTMP * s + yTMP*c;
    }
}