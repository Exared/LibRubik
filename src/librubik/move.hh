#pragma once

#include <variant>
namespace rubik
{
    enum class Axis
    {
        X,
        Y,
        Z
    };

    enum class Direction
    {
        CLOCKWISE,
        ANTI_CLOCKWISE
    };

    enum class Face
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FRONT,
        BACK
    };

    class Move
    {
    public:
        std::variant<Face, Axis> mvt;
        Direction dir = Direction::CLOCKWISE;
        bool is_double = false;
    };

} // namespace rubik
