#include <iostream>
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

class Chess
{
private:
    Piece *arr[64];
    Color turn;

public:
    Chess() : turn(Color::WHITE)
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
        
        // Add a single rook
        arr[63] = new Rook(Color::BLACK, 63);
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

    bool isEmpty(int position) const {
        return arr[position] == nullptr || arr[position]->getColor() != turn;
    }

    bool move(int oldPosition, int newPosition) {
        if (arr[oldPosition] == nullptr || arr[oldPosition]->getColor() != turn) {
            return false;
        }

        if (!arr[oldPosition]->move(newPosition)) {
            return false;
        }

        if (!isEmpty(newPosition)) {
            delete arr[newPosition];  // Capture the opposing piece
        }

        arr[newPosition] = arr[oldPosition];
        arr[oldPosition] = nullptr;

        // Switch turn
        turn = (turn == Color::WHITE) ? Color::BLACK : Color::WHITE;

        return true;
    }
};