#include "piece.hpp"

std::vector<Position> Pawn::getPossibleMoves(Position start_position)
{
    // Create holder for our vector
    std::vector<Position> possible_moves {};
    
    possible_moves.push_back( start_position + Position{ 0 , 1 } );
    possible_moves.push_back( start_position + Position{ 0 , 2 } );

    return possible_moves;
}

std::vector<Position> Knight::getPossibleMoves(Position start_position)
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

    return possible_moves;
}
