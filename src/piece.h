#include <vector>

enum class Color
{
    WHITE,
    BLACK,
    NONE
};

enum class PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    NONE
};


class Piece
{
private:
    Color color;
    PieceType type;

public:
    Piece(Color color, PieceType type) : color(color), type(type) {}

    Color getColor() const { return color; }
    PieceType getType() const { return type; }
};