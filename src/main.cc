// FIXME: You can include various files from the librubik library
#include <array>
#include <fstream>
#include <librubik/cube.hh>

#include "librubik/color.hh"
#include "librubik/matrix3D.hh"
#include "librubik/move.hh"
#include "librubik/piece.hh"
#include "librubik/vector3D.hh"
#include "librubik/solver/f2l.hh"

using namespace rubik;
using namespace rubik::solver;

int main()
{
    // FIXME: This is where you should play around with librubik.
    // Do not forget to use the 'rubik' namespace prefix (rubik::Cube,
    // rubik::Move, ...)

    Cube cube;
    cube.do_moves(parse_moves("F' D' R2 x L' U B R F U2 F2 L2 L y2 F' B2 U2 D B' z'"));

    F2L f2l{"patterns/layer1_white_edges.csv"};

    f2l.load_patterns();
    auto moves = f2l.solve(cube);
    std::cout << cube ;

    return 0;
}
