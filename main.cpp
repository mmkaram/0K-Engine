#include "chess.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Chess chess;
    // Testing knight moves
    std::cout << chess.move(17, 0) << "\n";

    // Testing Rook moves
    std::cout << chess.move(63, 61) << "\n";
    
    // Testing Queen moves
    std::cout << chess.move(37, 19) << "\n";
    
    // Testing Bishop moves
    std::cout << chess.move(32, 41) << "\n";

    // Testing King moves
    std::cout << chess.move(4, 4+8) << "\n";

    // Testing Pawn moves
    std::cout << chess.move(8, 8+8) << "\n";


    // ------------------------------
    // Testing checks
    
}