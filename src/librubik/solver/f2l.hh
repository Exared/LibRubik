#pragma once

#include <vector>

#include "parse-csv.hh"
#include "solver.hh"
// First 2 Layers

namespace rubik::solver
{
    class F2L : public Solver
    {
    public:
        F2L(std::initializer_list<std::string> files);
        
        void load_patterns() override;
        void setup(Cube& cube) override;
        std::vector<Move> solve(Cube cube);

        Color top_face;
        Color banned_color;
        std::vector<std::string> files;
        std::vector<std::vector<std::vector<std::string>>> csvs;
    };

} // namespace rubik::solver
