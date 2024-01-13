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
        arr[37] = new Queen(Color::WHITE, 37);

        // Add a single rook
        arr[60] = new Rook(Color::BLACK, 60);

        // Add a single knight
        arr[17] = new Knight(Color::WHITE, 17);

        // Add a single bishop
        arr[32] = new Bishop(Color::BLACK, 32);

        // Add kings
        arr[59] = new King(Color::BLACK, 59);
        arr[4] = new King(Color::WHITE, 4);
    }

    // helper funcs
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
                board += "-- ";
            }
            else
            {
                board += (arr[i]->getColor() == Color::WHITE ? "W" : "B");
                board += arr[i]->getRenderChar();
                board += " ";
            }
        }

        board += "\n";
        return board;
    }

    bool isSameColor(int position, Color color) const
    {
        return arr[position] != nullptr && arr[position]->getColor() == color;
    }

    bool isEmpty(int position) const
    {
        return arr[position] == nullptr;
    }

    bool isInCheck(Color kingColor)
    {
        // Find the position of the king
        int kingPos = -1;
        for (int i = 0; i < 64; i++)
        {
            if (arr[i] != nullptr && arr[i]->getColor() == kingColor && dynamic_cast<King *>(arr[i]) != nullptr)
            {
                kingPos = i;
                break;
            }
        }

        // If the king is not on the board, it's not in check
        if (kingPos == -1)
        {
            std::cout << "king not found";
            return false;
        }
        printf("kingPos: ");
        std::cout << kingPos;
        printf("\n");
        // Check if any piece can move to the king's position
        for (int i = 0; i < 64; i++)
        {
            // check if the square is not empty, it's not it's own piece, and it has a valid move to the king
            if (arr[i] != nullptr && arr[i]->getColor() != kingColor && arr[i]->move(kingPos))
            {

                // DEBUG
                std::cout << "i is: " << i << "\n";
                std::array<int, 9> path = arr[i]->getPath(kingPos);
                std::cout << "path is: ";

                for (int j = 0; j < 9; j++)
                {
                    std::cout << path[j];
                    std::cout << " ";
                }

                // DEBUG

                for (int j = 0; j < 9; j++)
                {
                    if (path[j] == kingPos)
                    {
                        std::cout << "path[j] is kingPos\n";
                        return true;
                    }
                    if (!isEmpty(path[j]) || path[j] == -1)
                    {
                        std::cout << "something in the way or no more path\n";
                        continue;
                    }
                    else
                    {
                        std::cout << "path[j] is empty\n";
                        continue;
                    }
                    std::cout << "Done with current piece: ";
                    std::cout << arr[i];
                    std::cout << "\n";
                }
            }
        }
        std::cout << "king is not in check\n";
        // If no piece can move to the king's position, the king is not in check
        return false;
    }

    int move(int oldPosition, int newPosition)
    {
        // Checks if the piece in the square that's trying to move exists
        if (arr[oldPosition] == nullptr)
        {
            std::cout << "this is a null pointer\n";
            return 1;
        }
        // Checks if that piece can be moved
        if ((arr[oldPosition]->getColor() != turn))
        {
            std::cout << "this is not your piece\n";
            return 2;
        }

        // Checks if there's a piece in the way
        std::array<int, 9> PATH = arr[oldPosition]->getPath(newPosition);
        // for i in the path to the end goal position
        for (int i = 0; i < 9; i++)
        {
            std::cout << "Steps will be taken to get to intended result"<< PATH[i];
            // if the next value in the path is the last
            // check if the piece in the last position is the same color
            if (PATH[i + 1] == -1)
            {
                if (isSameColor(newPosition, arr[oldPosition]->getColor()))
                {
                    std::cout << "You cannot capture your own piece\n";
                    return 5;
                }
                break;
            }
            // if there's a piece in the way, this move is invalid
            else if (!isEmpty(PATH[i]))
            {
                std::cout << "There is a piece in the way";
                std::cout << PATH[i];
                std::cout << "\n";
                return 3;
            }
        }

        if (!arr[oldPosition]->move(newPosition))
        {
            std::cout << "Invalid move\n";
            return 4;
        }

        Piece *capturedPiece = arr[newPosition];
        if (!isEmpty(newPosition) && !isSameColor(newPosition, arr[oldPosition]->getColor()))
        {
            std::cout << "You captured a piece\n";
            delete arr[newPosition]; // Capture the opposing piece
        }
        arr[oldPosition]->setPosition(newPosition); // Update the piece's position
        arr[newPosition] = arr[oldPosition];
        arr[oldPosition] = nullptr;

        if (isInCheck(turn))
        {
            std::cout << "You cannot move into check\n";
            // Undo the move
            arr[newPosition]->setPosition(oldPosition);
            arr[oldPosition] = arr[newPosition];
            arr[newPosition] = nullptr;
            arr[newPosition] = capturedPiece;
            delete capturedPiece;
            return 6;
        }

        // Switch turn
        turn = (turn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        std::cout << this->getBoard() << "\n";
        std::cout << "It is now " << colorToString(turn) << "'s turn.\n";

        return 0;
    }
};