#include <iostream>
#include "pieces/pawn.h"
#include "pieces/queen.h"

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

        // Add a single queen
        arr[37] = new Queen(Color::WHITE, 32);
    }

    std::string getBoard() const
    {
        std::string board;
        for (int i = 0; i < 64; i++)
        {
            if (i % 8 == 0)
            {
                board += "\n";
            }

            if (arr[i] == nullptr)
            {
                board += "- ";
            }
            else
            {
                board += (arr[i]->getColor() == Color::WHITE ? "W " : "B ");
            }
        }

        board += "\n";
        return board;
    }

    bool
    isEmpty(int position) const
    {
        return arr[position] == nullptr;
    }
    bool move(int oldPosition, int newPosition)
    {
        if (isEmpty(oldPosition))
        {
            return false;
        }

        if (arr[oldPosition]->move(newPosition))
        {
            arr[oldPosition]->setPosition(newPosition);
            arr[newPosition] = arr[oldPosition];
            arr[oldPosition] = nullptr;
            return true;
        }
        else
        {
            return false;
        }
    }
};