#pragma once
#include "Position.hpp"
#include <vector>
#include <map>

enum Pieces
{
    Empty,
    WhitePawn,
    WhiteKnight,
    WhiteBishop,
    WhiteRook,
    WhiteQueen,
    WhiteKing,
    BlackPawn,
    BlackKnight,
    BlackBishop,
    BlackRook,
    BlackQueen,
    BlackKing
};

// Takes a board and returns
class Piece {
    public:
        virtual std::vector<Position> getPossibleMoves(Position start_position);
        Piece(int id);
        ~Piece();

        static Piece* getPieceFromId(int id);

    private:
        int id {-1};
        static std::map<int, Piece> piece_map;

};

class Pawn : Piece {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override;
};

class Rook : Piece {
    
};

class Knight : Piece { 
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override;
};

class Bishop : Piece {
    
};

class Queen : Piece {
    
};

class King : Piece {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override;
};
