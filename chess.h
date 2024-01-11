#include <iostream>
#include "pieces/pawn.h"

class Chess
{
private:
    Piece *arr[64];

public:
    Chess()
    {
        // Initialize all squares to nullptr
        for (int i = 0; i < 64; i++)
        {
            arr[i] = nullptr;
        }

        // Place white pawns at indices 8-15
        for (int i = 8; i < 16; i++)
        {
            arr[i] = new Pawn(Color::WHITE, i);
        }

        // Place black pawns at indices 48-55
        for (int i = 48; i < 56; i++)
        {
            arr[i] = new Pawn(Color::BLACK, i);
        }
    }
    void printBoard() const
    {
        for (int i = 0; i < 64; i++)
        {
            if (i % 8 == 0)
            {
                std::cout << "\n";
            }

            if (arr[i] == nullptr)
            {
                std::cout << "- ";
            }
            else
            {
                std::cout << (arr[i]->getColor() == Color::WHITE ? "W" : "B") << " ";
            }
        }

        std::cout << "\n";
    }
};