#include "cube.hh"

#include <fstream>
#include <sstream>
#include <variant>

namespace rubik
{
    Cube::Cube()
        : pieces_(std::vector<Piece>())
    {
        int layer = -1;
        int abs = -1;
        int ord = -1;
        for (size_t i = 0; i < 3; i++)
        {
            abs = -1;
            for (size_t j = 0; j < 3; j++)
            {
                ord = -1;
                for (size_t k = 0; k < 3; k++)
                {
                    Piece p = { { abs, ord, layer },
                                { Color::NONE, Color::NONE, Color::NONE } };
                    if (layer == -1)
                        p.colors.z = Color::YELLOW;
                    if (layer == 1)
                        p.colors.z = Color::WHITE;
                    if (ord == -1)
                        p.colors.y = Color::ORANGE;
                    if (ord == 1)
                        p.colors.y = Color::RED;
                    if (abs == 1)
                        p.colors.x = Color::GREEN;
                    if (abs == -1)
                        p.colors.x = Color::BLUE;
                    pieces_.push_back(p);
                    ord++;
                }
                abs++;
            }
            layer++;
        }
    }

    Color letter_to_color(char c)
    {
        if (c == 'R')
            return Color::RED;
        if (c == 'G')
            return Color::GREEN;
        if (c == 'B')
            return Color::BLUE;
        if (c == 'O')
            return Color::ORANGE;
        if (c == 'Y')
            return Color::YELLOW;
        if (c == 'W')
            return Color::WHITE;
        return Color::NONE;
    }

    Cube Cube::from_stream(std::istream& is)
    {
        Cube cube;
        std::string line;
        std::string word;
        size_t i = 0;
        int x = 0;
        int y = 0;
        int z = 0;
        char c1 = 'X';
        char c2 = 'X';
        char c3 = 'X';
        while (std::getline(is, line))
        {
            int check = sscanf(line.c_str(), "(%d,%d,%d) (%c,%c,%c)\n", &x, &y,
                               &z, &c1, &c2, &c3);
            if (check != 6)
                throw std::invalid_argument("");
            cube.pieces_[i].coords.x = x;
            cube.pieces_[i].coords.y = y;
            cube.pieces_[i].coords.z = z;
            cube.pieces_[i].colors.x = letter_to_color(c1);
            cube.pieces_[i].colors.y = letter_to_color(c2);
            cube.pieces_[i].colors.z = letter_to_color(c3);
            i++;
        }
        return cube;
    }

    std::ostream& operator<<(std::ostream& os, const Cube& c)
    {
        size_t len = c.pieces_.size();
        for (size_t i = 0; i < len; i++)
        {
            os << c.pieces_[i] << "\n";
        }
        return os;
    }

    std::vector<Piece>::iterator Cube::begin()
    {
        return pieces_.begin();
    }

    std::vector<Piece>::iterator Cube::end()
    {
        return pieces_.end();
    }

    std::vector<Piece>::const_iterator Cube::begin() const
    {
        return pieces_.cbegin();
    }

    std::vector<Piece>::const_iterator Cube::end() const
    {
        return pieces_.cend();
    }

    Piece Cube::find_piece(Vector3D<int> coords) const
    {
        if (coords.x < -1 || coords.x > 1)
            throw std::invalid_argument("");
        if (coords.y < -1 || coords.y > 1)
            throw std::invalid_argument("");
        if (coords.z < -1 || coords.z > 1)
            throw std::invalid_argument("");
        for (size_t i = 0; i < pieces_.size(); i++)
        {
            if (pieces_[i].coords == coords)
                return pieces_[i];
        }
        return pieces_[0];
    }

    Piece Cube::find_piece(Vector3D<Color> colors) const
    {
        auto x = std::vector<Color>({ colors.x, colors.y, colors.z });
        std::sort(x.begin(), x.end());
        for (Piece p : pieces_)
        {
            auto y = std::vector<Color>({ p.colors.x, p.colors.y, p.colors.z });
            std::sort(y.begin(), y.end());
            if (x == y)
                return p;
        }
        throw std::invalid_argument("");
    }

    void Cube::do_move(Move move)
    {
        if (std::get_if<Axis>(&move.mvt))
        {
            for (Piece& p : pieces_)
            {
                p.do_move(std::get<Axis>(move.mvt), move.dir);
                if (move.is_double)
                    p.do_move(std::get<Axis>(move.mvt), move.dir);
            }
        }
        else
        {
            if (std::get<Face>(move.mvt) == Face::FRONT)
            {
                for (Piece& p : pieces_)
                {
                    if (p.coords.x == 1)
                    {
                        p.do_move(std::get<Face>(move.mvt), move.dir);
                        if (move.is_double)
                            p.do_move(std::get<Face>(move.mvt), move.dir);
                    }
                }
            }
            else if (std::get<Face>(move.mvt) == Face::BACK)
            {
                for (Piece& p : pieces_)
                {
                    if (p.coords.x == -1)
                    {
                        p.do_move(std::get<Face>(move.mvt), move.dir);
                        if (move.is_double)
                            p.do_move(std::get<Face>(move.mvt), move.dir);
                    }
                }
            }
            else if (std::get<Face>(move.mvt) == Face::RIGHT)
            {
                for (Piece& p : pieces_)
                {
                    if (p.coords.y == 1)
                    {
                        p.do_move(std::get<Face>(move.mvt), move.dir);
                        if (move.is_double)
                            p.do_move(std::get<Face>(move.mvt), move.dir);
                    }
                }
            }
            else if (std::get<Face>(move.mvt) == Face::LEFT)
            {
                for (Piece& p : pieces_)
                {
                    if (p.coords.y == -1)
                    {
                        p.do_move(std::get<Face>(move.mvt), move.dir);
                        if (move.is_double)
                            p.do_move(std::get<Face>(move.mvt), move.dir);
                    }
                }
            }
            else if (std::get<Face>(move.mvt) == Face::UP)
            {
                for (Piece& p : pieces_)
                {
                    if (p.coords.z == 1)
                    {
                        p.do_move(std::get<Face>(move.mvt), move.dir);
                        if (move.is_double)
                            p.do_move(std::get<Face>(move.mvt), move.dir);
                    }
                }
            }
            else if (std::get<Face>(move.mvt) == Face::DOWN)
            {
                for (Piece& p : pieces_)
                {
                    if (p.coords.z == -1)
                    {
                        p.do_move(std::get<Face>(move.mvt), move.dir);
                        if (move.is_double)
                            p.do_move(std::get<Face>(move.mvt), move.dir);
                    }
                }
            }
        }
    }

    void Cube::do_moves(std::vector<Move> moves)
    {
        for (Move m : moves)
            do_move(m);
    }

    void Cube::undo_move(Move move)
    {
        Direction direc = Direction::CLOCKWISE;
        if (move.dir == Direction::CLOCKWISE)
            direc = Direction::ANTI_CLOCKWISE;
        do_move(Move{ move.mvt, direc, move.is_double });
    }

    void Cube::undo_moves(std::vector<Move> moves)
    {
        for (Move m : moves)
            undo_move(m);
    }

    std::variant<Face, Axis> char_to_face(std::string str)
    {
        if (str[0] == 'F')
            return Face::FRONT;
        if (str[0] == 'B')
            return Face::BACK;
        if (str[0] == 'L')
            return Face::LEFT;
        if (str[0] == 'R')
            return Face::RIGHT;
        if (str[0] == 'U')
            return Face::UP;
        if (str[0] == 'D')
            return Face::DOWN;
        if (str[0] == 'x')
            return Axis::X;
        if (str[0] == 'y')
            return Axis::Y;
        return Axis::Z;
    }

    bool is_double(std::string str)
    {
        if (str.length() >= 2)
        {
            if (str[1] == '2')
                return true;
        }
        return false;
    }

    Direction get_dir(std::string str)
    {
        if (str.length() >= 2)
        {
            if (str[1] == '\'')
                return Direction::ANTI_CLOCKWISE;
        }
        return Direction::CLOCKWISE;
    }

    std::vector<Move> parse_moves(std::string input)
    {
        std::stringstream iss(input);
        std::string word;
        std::vector<Move> res = std::vector<Move>();
        while (iss >> word)
            res.push_back(
                Move{ char_to_face(word), get_dir(word), is_double(word) });
        return res;
    }

} // namespace rubik
