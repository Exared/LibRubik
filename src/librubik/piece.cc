#include "piece.hh"

#include "matrix3D.hh"
namespace rubik
{
    Piece::Piece(Vector3D<int> pos, Vector3D<Color> colors)
        : coords(pos)
        , colors(colors)
    {}

    std::ostream& operator<<(std::ostream& os, const Piece& p)
    {
        os << p.coords << " " << p.colors;
        return os;
    }

    Piece::Type Piece::get_type()
    {
        int z = 0;
        if (coords.x == 0)
            z++;
        if (coords.y == 0)
            z++;
        if (coords.z == 0)
            z++;
        if (z == 3)
            return NONE;
        if (z == 2)
            return CENTER;
        if (z == 1)
            return EDGE;
        return CORNER;
    }

    bool Piece::operator==(Piece& other)
    {
        if (other.colors == colors && other.coords == coords)
            return true;
        return false;
    }

    bool Piece::operator<(Piece& other)
    {
        int sum1 = coords.x + coords.y + coords.z;
        int sum2 = other.coords.x + other.coords.y + other.coords.z;
        if (sum1 < sum2)
            return true;
        return false;
    }

    bool Piece::operator!=(Piece& other)
    {
        if (*this == other)
            return false;
        return true;
    }

    bool Piece::operator<=(Piece& other)
    {
        if (*this == other || *this < other)
            return true;
        return false;
    }

    bool Piece::operator>(Piece& other)
    {
        if (*this <= other)
            return false;
        return true;
    }

    bool Piece::operator>=(Piece& other)
    {
        if (*this > other || *this == other)
            return true;
        return false;
    }

    void Piece::do_move(Face face, Direction dir)
    {
        auto rxclo =
            Matrix3D<int>{ { { { 1, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 } } } };
        auto ryclo =
            Matrix3D<int>{ { { { 0, 0, 1 }, { 0, 1, 0 }, { -1, 0, 0 } } } };
        auto rzclo =
            Matrix3D<int>{ { { { 0, -1, 0 }, { 1, 0, 0 }, { 0, 0, 1 } } } };
        auto rx =
            Matrix3D<int>{ { { { 1, 0, 0 }, { 0, 0, 1 }, { 0, -1, 0 } } } };
        auto ry =
            Matrix3D<int>{ { { { 0, 0, -1 }, { 0, 1, 0 }, { 1, 0, 0 } } } };
        auto rz =
            Matrix3D<int>{ { { { 0, 1, 0 }, { -1, 0, 0 }, { 0, 0, 1 } } } };
        if (dir == Direction::CLOCKWISE)
        {
            if (face == Face::UP)
            {
                rzclo.transpose();
                auto tmp = this->colors.x;
                this->colors.x = this->colors.y;
                this->colors.y = tmp;
                this->coords = rzclo * this->coords;
            }
            else if (face == Face::DOWN)
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.y;
                this->colors.y = tmp;
                this->coords = rzclo * this->coords;
            }
            else if (face == Face::FRONT)
            {
                auto tmp = this->colors.y;
                this->colors.y = this->colors.z;
                this->colors.z = tmp;
                rxclo.transpose();
                this->coords = rxclo * this->coords;
            }
            else if (face == Face::BACK)
            {
                auto tmp = this->colors.y;
                this->colors.y = this->colors.z;
                this->colors.z = tmp;
                this->coords = rxclo * this->coords;
            }
            else if (face == Face::RIGHT)
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.z;
                this->colors.z = tmp;
                ryclo.transpose();
                this->coords = ryclo * this->coords;
            }
            else
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.z;
                this->colors.z = tmp;
                this->coords = ryclo * this->coords;
            }
        }
        else
        {
            if (face == Face::UP)
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.y;
                this->colors.y = tmp;
                rz.transpose();
                this->coords = rz * this->coords;
            }
            else if (face == Face::DOWN)
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.y;
                this->colors.y = tmp;
                this->coords = rz * this->coords;
            }
            else if (face == Face::FRONT)
            {
                auto tmp = this->colors.y;
                this->colors.y = this->colors.z;
                this->colors.z = tmp;
                rx.transpose();
                this->coords = rx * this->coords;
            }
            else if (face == Face::BACK)
            {
                auto tmp = this->colors.y;
                this->colors.y = this->colors.z;
                this->colors.z = tmp;
                this->coords = rx * this->coords;
            }
            else if (face == Face::RIGHT)
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.z;
                this->colors.z = tmp;
                ry.transpose();
                this->coords = ry * this->coords;
            }
            else
            {
                auto tmp = this->colors.x;
                this->colors.x = this->colors.z;
                this->colors.z = tmp;
                this->coords = ry * this->coords;
            }
        }
    }

    void Piece::do_move(Axis axis, Direction dir)
    {
        if (axis == Axis::X) // Right
            do_move(Face::RIGHT, dir);
        else if (axis == Axis::Y)
            do_move(Face::UP, dir);
        else
            do_move(Face::FRONT, dir);
    }

} // namespace rubik
