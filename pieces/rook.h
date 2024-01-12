#include "piece.h"

class Rook : public Piece
{
public:
    Rook(Color color, int position) : Piece(color, position)
    {
        //
    }
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

        // Check if the move is along a rank or file
        if (oldX == newX || // Same file
            oldY == newY)   // Same rank
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