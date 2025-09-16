#include <array>
#include <unordered_map>

struct Position
{
    int x;
    int y;
};

template <int SizeX, int SizeY>
class Chessboard
{
    public:
        Chessboard()
        {

        }

        ~Chessboard()
        {

        }

        // Function overload to move a piece from start to end by raw stored number
        void movePiece(int start_position, int end_position)
        {
            this->board[end_position] = this->board[start_position];

            this->piece_map[this->board[end_position]] = end_position;
        }

        // Function overload to move a piece from start to end by struct position
        void movePiece(Position start_position, Position end_position)
        {
            int start_location = this->getLocationFromPosition(start_position);
            int end_location = this->getLocationFromPosition(end_position);

            this->movePiece(start_location, end_location);
        }

        // Takes in a piece ID and returns a position
        Position getPiecePosition(int piece_id)
        {
            return (this->getPositionFromLocation(this->piece_map[piece_id]));
        }

        // Takes an an x integer and y integer, returns the id of the piece at the position
        int getPieceAtPosition(Position position)
        {
            return this->board[this->getLocationFromPosition(position)];
        }

        // Takes in a position and returns the raw location in the array
        int getLocationFromPosition(Position position)
        {
            // Offset for allowing Position to start at (1,1)
            int offset = this->sizeY + 1; 
            int location = (position.y * this->sizeY) + this->sizeX;

            return location - offset;
        }

        // Takes in a raw location in the array and returns a position
        Position getPositionFromLocation(int location)
        {

            // calculate offset to start at (1,1)
            int offset = this->sizeY  + 1;
            int new_location = location + offset;

            // Now calculate x and y
            int position_y = new_location / this->sizeY;
            int position_x = (new_location % this->sizeY) + 1;

            return Position{position_x, position_y};
        }

    // Chessboard is stored as an array of size (x * y)
    private:
        // Store size of board for calculations
        const int sizeX{SizeX};
        const int sizeY{SizeY};

        // Board is a list of integers with each element representing a space on the board
        // Starts from bottom left and moves right, until it hits SizeX, and then moves up one Y
        // Integer is an ID for every piece
        std::array<int, SizeX * SizeY> board{};

        // A hashmap that alternatively holds every piece, so we can lookup positions from just the piece
        // Key is the ID of the piece, the value is the integer position of the piece
        std::unordered_map<int, int> piece_map{};

};
