#include "piece.h"
#include <vector>
#include <algorithm>

class Knight : public Piece
{
public:
    Knight(Color color, int position) : Piece(color, position) {}

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            return false;
        }

        int difference = newPosition - position;
        std::vector<int> validMoves = {-17, -15, -10, -6, 6, 10, 15, 17};

        if (std::find(validMoves.begin(), validMoves.end(), difference) != validMoves.end())
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