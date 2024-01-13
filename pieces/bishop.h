#include "piece.h"
#include <iostream>

class Bishop : public Piece
{
private:
    int direction;

public:
    Bishop(Color color, int position) : Piece(color, position) {}

    char getRenderChar() const override { return 'B'; }

    std::array<int, 9> getPath(int newPosition) override
    {
        std::array<int, 9> path = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        int pos = this->position;
        int i = 0;

        // Check if the move is along a diagonal
        if (abs(newPosition - this->position) % 9 == 0 || abs(newPosition - this->position) % 7 == 0)
        {
            int step = this->position < newPosition ? 1 : -1;
            if (abs(newPosition - this->position) % 9 == 0)
                step *= 9; // moving diagonally right
            else if (abs(newPosition - this->position) % 7 == 0)
                step *= 7; // moving diagonally left

            while (pos != newPosition)
            {
                pos += step;
                path[i] = pos;
                i++;
            }
        }

        return path;
    }

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            std::cout << "kill yourself\n";
            return false;
        }

        int difference = abs(newPosition - position);

        // Check if the move is along a diagonal
        if (difference % 7 == 0 || difference % 9 == 0)
        {
            position = newPosition;
            return true;
        }
        return false;
    }
};