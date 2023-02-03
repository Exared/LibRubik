#include "f2l.hh"

namespace rubik::solver
{
    F2L::F2L(std::initializer_list<std::string> files)
    {
        for (auto file : files)
            this->files.push_back(file);
    }

    void F2L::load_patterns()
    {
        for (auto f : files)
        {
            std::vector<std::vector<std::string>> parsed = parse_csv(f);
            csvs.push_back(parsed);
        }
    }

    void F2L::setup(Cube& cube)
    {
        Piece top = cube.find_piece({0,0,1});
        top_face = top.colors.z;
        if (top_face == Color::WHITE)
            banned_color = Color::YELLOW;
        if (top_face == Color::YELLOW)
            banned_color = Color::WHITE;
        if (top_face == Color::BLUE)
            banned_color = Color::GREEN;
        if (top_face == Color::GREEN)
            banned_color = Color::BLUE;
        if (top_face == Color::RED)
            banned_color = Color::ORANGE;
        banned_color = Color::RED;
    }

    Color letter_to_col(char c, Color a, Color b)
    {
        if (c == 'a')
            return a;
        if (c == 'b')
            return b;
        return Color::NONE;
    }

    std::vector<Move> F2L::solve(Cube cube)
    {
        auto res = std::vector<Move>();
        Color front = cube.find_piece({1, 0, 0}).colors.x;
        auto target = cube.find_piece({top_face, front, Color::NONE});
        for (auto vect: csvs.at(1))
        {
            Vector3D<int> coord = {stoi(vect.at(0)), stoi(vect.at(1)), stoi(vect.at(2))};
            if (coord == target.coords)
            {
                Vector3D<Color> col = {letter_to_col(vect.at(3)[0], top_face, front), letter_to_col(vect.at(4)[0], top_face, front), letter_to_col(vect.at(5)[0], top_face, front)};
                if (col == target.colors)
                {
                    return parse_moves(vect.at(6));
                }
            }
        }
        return res;
    }

} // namespace rubik::solver
