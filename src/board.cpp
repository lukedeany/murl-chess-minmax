#include "board.hpp"

template <int SizeX, int SizeY>
Chessboard<SizeX, SizeY>::Chessboard()
{
    
}

template <int SizeX, int SizeY>
Chessboard<SizeX, SizeY>::~Chessboard()
{

}

template <int SizeX, int SizeY>
void Chessboard<SizeX, SizeY>::movePiece(int start_position, int end_position)
{
    this->board[end_position] = this->board[start_position];

    this->piece_map[this->board[end_position]] = end_position;
}

template <int SizeX, int SizeY>
void Chessboard<SizeX, SizeY>::movePiece(Position start_position, Position end_position)
{
    int start_location = this->getLocationFromPosition(start_position);
    int end_location = this->getLocationFromPosition(end_position);

    this->movePiece(start_location, end_location);
}

template <int SizeX, int SizeY>
Position Chessboard<SizeX, SizeY>::getPiecePosition(int piece)
{
    return (this->getPositionFromLocation(this->piece_map[piece]));
}
template <int SizeX, int SizeY>
int Chessboard<SizeX, SizeY>::getPieceAtPosition(Position position)
{
    return this->board[this->getLocationFromPosition(position)];
}

template <int SizeX, int SizeY>
int Chessboard<SizeX, SizeY>::getLocationFromPosition(Position position)
{
    // Offset for allowing Position to start at (1,1)
    int offset = this->sizeY + 1; 
    int location = (position.y * this->sizeY) + this->sizeX;

    return location - offset;
}

template <int SizeX, int SizeY>
Position Chessboard<SizeX, SizeY>::getPositionFromLocation(int location)
{
    // calculate offset to start at (1,1)
    int offset = this->sizeY  + 1;
    int new_location = location + offset;

    // Now calculate x and y
    int position_y = new_location / this->sizeY;
    int position_x = (new_location % this->sizeY) + 1;

    return Position{position_x, position_y};
}
