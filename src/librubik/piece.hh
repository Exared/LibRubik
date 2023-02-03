#pragma once

#include "color.hh"
#include "matrix3D.hh"
#include "move.hh"
#include "vector3D.hh"
namespace rubik
{
    class Piece
    {
    public:
        enum Type
        {
            NONE,
            CENTER,
            EDGE,
            CORNER
        };

        Piece(Vector3D<int> pos, Vector3D<Color> colors);

        Type get_type();

        bool operator==(Piece& other);

        bool operator<(Piece& other);

        bool operator!=(Piece& other);

        bool operator>(Piece& other);

        bool operator<=(Piece& other);

        bool operator>=(Piece& other);

        void do_move(Face face, Direction dir);

        void do_move(Axis axis, Direction dir);

        Vector3D<int> coords;
        Vector3D<Color> colors;
    };

    std::ostream& operator<<(std::ostream& os, const Piece& p);

} // namespace rubik
