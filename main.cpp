#include "chess.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Chess chess;
    // Testing knight moves
    std::cout << chess.move(17, 0) << "\n";

    std::cout << chess.move(63, 63-8) << "\n";
}