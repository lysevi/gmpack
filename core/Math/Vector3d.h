
#pragma once
#include <cmath>

namespace core {

    struct Vector3d {
        float x, y, z;

        Vector3d(const float _x, const float _y, const float _z) {
            x = _x;
            y = _y;
            z = _z;
        }
        Vector3d()=default;

        Vector3d* operator=(const Vector3d&right) {
            this->x = right.x;
            this->y = right.y;
            this->z = right.z;
            return this;
        }

        float length()const {
            return sqrt(x * x + y * y + z * z);
        }

        void norm() {
            auto len = length();
            x /= len;
            y /= len;
            z /= len;
        }
    };

    Vector3d operator+(const Vector3d&left, const Vector3d&right);

    Vector3d operator-(const Vector3d&left, const Vector3d&right);

    bool operator>(const Vector3d&left, const Vector3d&right);

    bool operator<(const Vector3d&left, const Vector3d&right);

    bool operator==(const Vector3d&left, const Vector3d&right);

    bool operator!=(const Vector3d&left, const Vector3d&right);

    Vector3d operator*(const Vector3d&left, const Vector3d&right);

    float dot(const Vector3d&left, const Vector3d&right);

    float distance(const Vector3d&from, const Vector3d&to);
}