#pragma once
#include "Position.hpp"
#include <vector>
#include <map>
#include <algorithm>

// C++ magic to say we want a template that actually has
// an implementation of getPossibleMoves, i.e. not pure virutal
template <typename PieceType>
concept ConcretePiece = requires (PieceType piece)
{
    { piece.getPossibleMoves( Position {0,0} ) };
};

enum class PieceColor
{
    PieceColorBlack,
    PieceColorWhite,
};

// Takes a board and returns
template <int SizeX, int SizeY>
class Piece {
    public:
        virtual std::vector<Position> getPossibleMoves(Position start_position) = 0;

        Piece(int &id, PieceColor color)
        {
            this->id = id;
            this->color = color;
        }

        ~Piece() 
        {

        }

        int getID()
        {
            return id;
        }

        static Piece* getPieceFromId(int id);

    protected:
        std::vector<Position> filterMoves( std::vector<Position> possible, Position starting_position )
        {
            
            // Create holder for our filter
            std::vector<Position> filtered_moves {};

            // Filter our given position
            // mostly c++ syntax sugar, but loops from begining to end of possible
            // and inserts into the back of filtered moves (back_inserter)
            // using the lambda function copying starting_position and our values.
            // in the end simply removes any values not within our size bounds or
            // moves that didn't actually move the piece
            std::copy_if(possible.begin(), possible.end(), 
                    std::back_inserter(filtered_moves), 
                    [starting_position](Position pos) 
                    { return (pos.x >= 0 && pos.x < SizeX && pos.y >= 0 && pos.y < SizeY) && 
                             !(pos.x == starting_position.x && pos.y == starting_position.y ); 
                    });

            // Finally, return our filtered data
            return filtered_moves;
        }

    private:
        PieceColor color;

        int id {-1};
        // piece map that will hold every piece and their id
        // maybe move to piecemaker?
        static std::map<int, Piece> piece_map;

};

template <int SizeX, int SizeY>
class Pawn : public Piece<SizeX, SizeY> {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override
        {
            // Create holder for our vector
            std::vector<Position> possible_moves {};
            
            possible_moves.push_back( start_position + Position{ 0 , 1 } );

            // special cases
            possible_moves.push_back( start_position + Position{ 0 , 2 } );
            possible_moves.push_back( start_position + Position { -1, 1 } );
            possible_moves.push_back( start_position + Position { 1, 1 } );

            // ensure correct constraints
            return this->filterMoves(possible_moves, start_position);
        }

        // constructor that calls parent constructor
        Pawn (int& id, PieceColor color): Piece<SizeX, SizeY>(id, color) {
            
        }
};

template <int SizeX, int SizeY>
class Rook : public Piece<SizeX, SizeY> {
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

            return this->filterMoves( possible_moves, start_position );
        }

        // constructor that calls parent constructor
        Rook (int& id, PieceColor color): Piece<SizeX, SizeY>(id, color) {
            
        }
};

template <int SizeX, int SizeY>
class Knight : public Piece<SizeX, SizeY> { 
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override
        {
            // Create holder for our vector
            std::vector<Position> possible_moves {};

            possible_moves.push_back( start_position + Position { 1, 2} );
            possible_moves.push_back( start_position + Position { 2, 1} );
            possible_moves.push_back( start_position + Position { -1, 2} );
            possible_moves.push_back( start_position + Position { -2, 1} );
            possible_moves.push_back( start_position + Position { -1, -2} );
            possible_moves.push_back( start_position + Position { -2, -1} );
            possible_moves.push_back( start_position + Position { 1, -2} );
            possible_moves.push_back( start_position + Position { 2, -1} );

            return this->filterMoves( possible_moves, start_position );
        }

        // constructor that calls parent constructor
        Knight (int& id, PieceColor color): Piece<SizeX, SizeY>(id, color) {
            
        }
};

template <int SizeX, int SizeY>
class Bishop : public Piece<SizeX, SizeY> {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override 
        {
            // hold our moves
            std::vector<Position> possible_moves {};

            // Now bishop can move any variation of x,y as long as |x| = |y|
            for (int i = 1; i < SizeY; i++)
            {
                possible_moves.push_back(start_position + Position { i, i } );
                possible_moves.push_back(start_position + Position { -i, i } );
                possible_moves.push_back(start_position + Position { i, -i } );
                possible_moves.push_back(start_position + Position { -i, -i } );
            }

            return this->filterMoves( possible_moves,  start_position );
        }

        // constructor that calls parent constructor
        Bishop (int& id, PieceColor color): Piece<SizeX, SizeY>(id, color) {
            
        }
};

template <int SizeX, int SizeY>
class Queen : public Piece<SizeX, SizeY> {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override 
        {
            // hold our moves
            std::vector<Position> possible_moves {};

            // Now bishop can move any variation of x,y as long as |x| = |y|
            for (int i = 1; i < SizeY; i++)
            {
                possible_moves.push_back(start_position + Position { i, i } );
                possible_moves.push_back(start_position + Position { -i, i } );
                possible_moves.push_back(start_position + Position { i, -i } );
                possible_moves.push_back(start_position + Position { -i, -i } );
            }

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
            
            return this->filterMoves( possible_moves, start_position );
        }

        // constructor that calls parent constructor
        Queen (int& id, PieceColor color): Piece<SizeX, SizeY>(id, color) {
            
        }
};

template <int SizeX, int SizeY>
class King : public Piece<SizeX, SizeY> {
    public:
        std::vector<Position> getPossibleMoves(Position start_position) override
        {
            // Create holder for our vector
            std::vector<Position> possible_moves {};

            possible_moves.push_back(start_position + Position {1, 0});
            possible_moves.push_back(start_position + Position {1, 1});
            possible_moves.push_back(start_position + Position {1, -1});
            possible_moves.push_back(start_position + Position {0, 0});
            possible_moves.push_back(start_position + Position {0, 1});
            possible_moves.push_back(start_position + Position {0, -1});
            possible_moves.push_back(start_position + Position {-1, 0});
            possible_moves.push_back(start_position + Position {-1, 1});
            possible_moves.push_back(start_position + Position {-1, -1});

            return this->filterMoves( possible_moves, start_position );
        }

        // constructor that calls parent constructor
        King (int& id, PieceColor color): Piece<SizeX, SizeY>(id, color) {
            
        }
};
