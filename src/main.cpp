#include <iostream>
#include "chess.h"

int main(int argc, char *argv[])
{
    Chess chess;

    std::cout << chess.boardString() << "\n";
    
    std::cout << chess.canMovePiece(17, 17+9) << "\n";

    
    return 0;
}