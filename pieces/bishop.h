#include "piece.h"
#include <iostream>

class Bishop : public Piece
{
private:
    int direction;

public:
    Bishop(Color color, int position) : Piece(color, position) {}

    char getRenderChar() const override { return 'B'; }

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
            std::cout << "va niquer ta mere\n";
            position = newPosition;
            return true;
        }
        std::cout << "hang yourself\n";
        return false;
    }
};