enum class COLOR
{
    WHITE,
    BLACK,
    NONE
};

enum class TYPE
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

class Piece
{
private:
    COLOR side;
    TYPE type;
public:
    Piece(COLOR color, TYPE piece){
        this->side = color;
        this->type = piece;
    }
    COLOR getSide(){
        std::string woo = std::to_string(static_cast<int>(this->side));
        return this->side;
    }
    TYPE getType(){
        return type;
    }
};
