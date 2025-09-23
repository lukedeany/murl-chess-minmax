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

template <int SizeX, int SizeY>
class Rook : Piece {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override 
        {
            // hold our moves
            std::vector<Position> possible_moves {};

            // Let rook move to any position
            for (int i = 0; i < SizeY; i++)
            {
                // ensure we dont have same position as nothing
                if (i != start_position.y) possible_moves.push_back(Position { start_position.x, i } );
            }

            for (int i = 0; i < SizeX; i++)
            {
                if (i != start_position.x) possible_moves.push_back(Position { i, start_position.y } );
            }

            return possible_moves;
        }
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
