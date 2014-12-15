#include "Vector3d.h"
#include <cmath>

namespace core{

 Vector3d operator+(const Vector3d&left, const Vector3d&right) {
        return Vector3d{left.x + right.x, left.y + right.y, left.z + right.z};
    }

    Vector3d operator-(const Vector3d&left, const Vector3d&right) {
        return Vector3d{left.x - right.x, left.y - right.y, left.z - right.z};
    }

    bool operator>(const Vector3d&left, const Vector3d&right) {
        return left.x > right.x && left.y > right.y && left.z > right.z;
    }

    bool operator<(const Vector3d&left, const Vector3d&right) {
        return left.x < right.x && left.y < right.y && left.z < right.z;
    }

    bool operator==(const Vector3d&left, const Vector3d&right) {
        return left.x == right.x && left.y == right.y && left.z == right.z;
    }

    bool operator!=(const Vector3d&left, const Vector3d&right) {
        return left.x != right.x || left.y != right.y || left.z != right.z;
    }

    Vector3d operator*(const Vector3d&left, const Vector3d&right) {
        return Vector3d{left.x * right.x, left.y * right.y, left.z * right.z};
    }

    float dot(const Vector3d&left, const Vector3d&right) {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }
}