#include "piece.h"
#include <algorithm>

class Knight : public Piece
{
public:
    Knight(Color color, int position) : Piece(color, position) {}
    
    char getRenderChar() const override { return 'N'; }
    
    std::array<int, 9> getPath(int newPosition) override {
        std::array<int, 9> a = {newPosition, -1, -1, -1, -1, -1, -1, -1, -1};
        return a;
    } 

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            return false;
        }

        int difference = newPosition - position;
        std::array<int, 8> validMoves = {-17, -15, -10, -6, 6, 10, 15, 17};

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