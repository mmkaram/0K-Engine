#include <iostream>
#include <string> 
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/king.h"

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

        // Add a single knight
        arr[17] = new Knight(Color::WHITE, 17);
        
        // Add a single bishop
        arr[32] = new Bishop(Color::BLACK, 32);

        // Add black king
        arr[60] = new King(Color::BLACK, 60);
    }

    std::string numberBoard()
    {
        std::string board;

        for (int i = 0; i < 64; i++)
        {
            if (i % 8 == 0 && i != 0)
            {
                board += "\n";
            }

            board += std::to_string(i);
            board += " ";
        }

        board += "\n";
        return board;
    }

    std::string colorToString(Color color)
    {
        switch (color)
        {
        case Color::WHITE:
            return "White";
        case Color::BLACK:
            return "Black";
        default:
            return "Unknown";
        }
    }

    Color getTurn() const
    {
        return turn;
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

    bool isEmpty(int position) const
    {
        return arr[position] == nullptr || arr[position]->getColor() != turn;
    }

    int move(int oldPosition, int newPosition)
    {
        if (arr[oldPosition] == nullptr || arr[oldPosition]->getColor() != turn)
        {
            return 1;
        }

        if (!arr[oldPosition]->move(newPosition))
        {
            return 2;
        }

        if (!isEmpty(newPosition))
        {
            delete arr[newPosition]; // Capture the opposing piece
        }

        arr[newPosition] = arr[oldPosition];
        arr[oldPosition] = nullptr;

        // Switch turn
        turn = (turn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        std::cout << this->getBoard() << "\n";
        std::cout << "It is now " << colorToString(turn) << "'s turn.\n";

        return 3;
    }
};