
#pragma once

namespace core {

    class Vector3d {
    public:
        Vector3d();
        Vector3d(float x, float y, float z);
        Vector3d(const Vector3d& orig);
        virtual ~Vector3d();
        bool operator==(const Vector3d& orig)const;

        bool operator!=(const Vector3d &A);
        // Multiply

        float operator*(const Vector3d &B);

        Vector3d operator ^ (const float C);

        Vector3d operator/(const float C);

        void operator*=(float C);

        // Add
        Vector3d operator+(const Vector3d &A);

        void operator+=(const Vector3d &A);
        // Subtract

        Vector3d operator-(const Vector3d &A);

        void operator-=(const Vector3d &A);

        float Length();
        void  Normalise();

        static void RotatePoint(Vector3d *Point,const Vector3d& Angle);
    public:
        float x, y, z;
    };

}