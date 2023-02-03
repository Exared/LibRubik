#pragma once

#include <iostream>

namespace rubik
{
    enum class Color
    {
        WHITE,
        YELLOW,
        GREEN,
        BLUE,
        RED,
        ORANGE,
        NONE
    };

    inline std::ostream& operator<<(std::ostream& os, const Color& c)
    {
        if (c == Color::WHITE)
            os << "W";
        if (c == Color::YELLOW)
            os << "Y";
        if (c == Color::BLUE)
            os << "B";
        if (c == Color::GREEN)
            os << "G";
        if (c == Color::RED)
            os << "R";
        if (c == Color::ORANGE)
            os << "O";
        if (c == Color::NONE)
            os << "X";
        return os;
    }

} // namespace rubik
