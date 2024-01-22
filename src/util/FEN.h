#include <string>
#include <sstream>
#include <vector>

struct FenParser {
    std::string piecePlacement;
    char activeColor;
    std::string castlingAvailability;
    std::string enPassantTargetSquare;
    int halfmoveClock;
    int fullmoveNumber;

    void parseFen(const std::string& fen) {
        std::istringstream iss(fen);
        iss >> piecePlacement;
        iss >> activeColor;
        iss >> castlingAvailability;
        iss >> enPassantTargetSquare;
        iss >> halfmoveClock;
        iss >> fullmoveNumber;
    }
};

int main() {
    FenParser parser;
    parser.parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    return 0;
}