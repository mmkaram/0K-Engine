#include "piece.h"

class Bishop : public Piece
{
private:
    int direction;

public:
    Bishop(Color color, int position) : Piece(color, position) {}

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            return false;
        }

        int difference = abs(newPosition - position);

        // Check if the move is along a diagonal
        if (difference % 7 == 0 || difference % 9 == 0)
        {
            // Check if the old and new positions are on the same diagonal
            int oldDiagonal = (position / 8) + (position % 8);
            int newDiagonal = (newPosition / 8) + (newPosition % 8);

            if (oldDiagonal == newDiagonal || oldDiagonal == -newDiagonal)
            {
                position = newPosition;
                return true;
            }
        }

        return false;
    }
};