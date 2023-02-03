#pragma once

#include <array>

#include "vector3D.hh"
namespace rubik
{
    template <class T>
    class Matrix3D
    {
    public:
        Matrix3D(std::array<std::array<T, 3>, 3> arr)
            : matrix_{ arr }
        {}

        T at(int i, int j)
        {
            return matrix_[i][j];
        }

        Vector3D<T> operator*(const Vector3D<T>& v) const
        {
            T x =
                v.x * matrix_[0][0] + v.y * matrix_[0][1] + v.z * matrix_[0][2];
            T y =
                v.x * matrix_[1][0] + v.y * matrix_[1][1] + v.z * matrix_[1][2];
            T z =
                v.x * matrix_[2][0] + v.y * matrix_[2][1] + v.z * matrix_[2][2];
            return Vector3D<T>{ x, y, z };
        }

        void transpose()
        {
            size_t start = 0;
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = start; j < 3; j++)
                {
                    T tmp = matrix_[i][j];
                    matrix_[i][j] = matrix_[j][i];
                    matrix_[j][i] = tmp;
                }
                start++;
            }
        }

    private:
        std::array<std::array<T, 3>, 3> matrix_;
    };

} // namespace rubik
