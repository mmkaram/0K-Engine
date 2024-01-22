#include <iostream>

class ChessBoard
{
public:
    // Constants for color
    static const int NULL_COLOR = 0b00;
    static const int WHITE_COLOR = 0b01;
    static const int BLACK_COLOR = 0b11;

    // Constants for piece types
    static const int NULL_TYPE = 0b0000;

    static const int PAWN = 0b0001;
    static const int KNIGHT = 0b0010;
    static const int BISHOP = 0b0011;
    static const int ROOK = 0b0100;
    static const int QUEEN = 0b0101;
    static const int KING = 0b0111;

private:
    int turn = WHITE_COLOR;
    int board[8][8];

public:
    // Constructor
    ChessBoard()
    {
        // Initialize the board with NULL pieces
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                board[i][j] = createPiece(NULL_COLOR, NULL_TYPE);
            }
        }
    }

    // Function to set a piece on the board
    void setPiece(int row, int col, int color, int type)
    {
        board[row][col] = createPiece(color, type);
    }

    // Function to get a piece from the board
    int getPiece(int row, int col) const
    {
        return board[row][col];
    }

    // Function to create a piece value
    static int createPiece(int color, int type)
    {
        return (color << 6) | type;
    }

    int getTurn() const
    {
        return turn;
    }
};

class moveGen
{
private:
};