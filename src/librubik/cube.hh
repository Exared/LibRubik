#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "move.hh"
#include "piece.hh"

namespace rubik
{
    class Cube
    {
    public:
        Cube();
        static Cube from_stream(std::istream& is);

        friend std::ostream& operator<<(std::ostream& os, const Cube& c);

        std::vector<Piece>::iterator begin();

        std::vector<Piece>::iterator end();

        std::vector<Piece>::const_iterator begin() const;

        std::vector<Piece>::const_iterator end() const;

        Piece find_piece(Vector3D<int> coords) const;

        Piece find_piece(Vector3D<Color> colors) const;

        void do_move(Move move);

        void do_moves(std::vector<Move> moves);

        void undo_move(Move move);

        void undo_moves(std::vector<Move> moves);

    private:
        std::vector<Piece> pieces_;
    };

    std::vector<Move> parse_moves(std::string input);

} // namespace rubik
