#pragma once

#include <iostream>
namespace rubik
{
    template <class T>
    class Vector3D
    {
    public:
        Vector3D(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {}

        friend inline std::ostream& operator<<(std::ostream& os,
                                               const Vector3D& vect)
        {
            os << "(" << vect.x << "," << vect.y << "," << vect.z << ")";
            return os;
        }

        bool operator==(const Vector3D& other)
        {
            if (this->x == other.x && this->y == other.y && this->z == other.z)
                return true;
            return false;
        }

        bool operator!=(const Vector3D& other)
        {
            if (this->x == other.x && this->y == other.y && this->z == other.z)
                return false;
            return true;
        }

        T x;
        T y;
        T z;
    };
} // namespace rubik
