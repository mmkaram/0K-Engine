#include "piece.h"

class King : public Piece
{
public:
    King(Color color, int position) : Piece(color, position) {}

    char getType() const { return 'K'; }

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            return false;
        }

        int oldX = position % 8;
        int oldY = position / 8;
        int newX = newPosition % 8;
        int newY = newPosition / 8;

        // Check if the move is one square in any direction
        if (abs(oldX - newX) <= 1 && abs(oldY - newY) <= 1)
        {
            position = newPosition;
            return true;
        }
        else
        {
            return false;
        }
    }
};