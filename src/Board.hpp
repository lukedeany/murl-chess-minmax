#include <array>
#include <unordered_map>
#include <memory>
#include <optional>
#include "Position.hpp"
#include "Piece.hpp"

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
            int start_location { this->getLocationFromPosition(start_position) };
            int end_location { this->getLocationFromPosition(end_position) };

            this->movePiece(start_location, end_location);
        }

        // Takes in a position and a color, returns true if the color at the given position is opposite
        // of the color given to the function, or if the space is empty!
        bool canColorMoveToPosition(Position position, PieceColor color)
        {
            // First we check the id at the position
            int piece_id = getPieceAtPosition(position);

            // If space is empty, we can move there!
            if (!piece_id)
            {
                return true;
            }

            // Now attempt to load in the piece from the id
            if ( std::unique_ptr<Piece<SizeX, SizeY>> located_piece { std::move(id_map.at(piece_id)) } )
            {
                // Piece exists, now extract color
                PieceColor found_color { located_piece.get()->getColor() };

                // also return our piece back
                id_map[piece_id] = std::move(located_piece) ;

                // Now return if the color is not the same as our passed color
                return found_color != color;
            }

            // We failed to load in anything, meaning an unregistered piece exists on the board
            // this is undefined behavior but return true for fun
            return true;
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
        
        // Check all valid moves! Takes in a piece ID
        // returns either a vector of valid positions if the piece exists,
        // otherwise returns nullopt
        std::optional<std::vector<Position>> getAllValidMovesForPiece(int piece_id)
        {
            if ( std::unique_ptr<Piece<SizeX, SizeY>> piece { std::move(this->id_map[piece_id]) } )
            {
                // Now get our location from piece ID
                int location { piece_map[piece_id] };

                // Now turn our location into a position
                Position pos { getPositionFromLocation(location) };

                PieceColor color { piece.get()->getColor() };

                // now create a holder for our positions and our filtered positions
                std::vector<Position> positions { piece.get()->getPossibleMoves(piece.pos) };
                std::vector<Position> filtered {};

                // Now filter our positions based on whether we can match
                std::copy_if( positions.begin(), positions.end(), std::back_inserter(filtered), [this, color](Position p) {
                    return this->canColorMoveToPosition(p, color);
                });

                // finally also return our piece back to it's correct position
                this->id_map[piece_id] = std::move(piece);

                // and return our filtered list
                return filtered;
            }

            return std::nullopt;
        }

        // Set a piece at a specific location
        void setPieceAtLocation(int location, int piece_id)
        {
            piece_map[piece_id] = location;

            board[location] = piece_id;
        }

        // Register pieces with our id_map
        // Takes in a unique pointer to a piece, which means we will take ownership of it.
        // also takes in the initial position to spawn it at
        void registerPiece( std::unique_ptr<Piece<SizeX, SizeY>> piece, Position position)
        {
            // get our ID then set our piece in our ID map
            int id { piece.get()->getID() };
            
            // Also set our initial position
            setPieceAtPosition(position, id);

            // Also add our value to our map, making sure to move it once more
            id_map[id] = std::move(piece);
        }

        // Set a piece based on a position
        void setPieceAtPosition(Position position, int piece_id)
        {
            // Turn our position into location
            int location { this->getLocationFromPosition(position) };

            this->setPieceAtLocation(location, piece_id);
        }


        // Takes in a position and returns the raw location in the array
        int getLocationFromPosition(Position position)
        {
            // Offset for allowing Position to start at (1,1)
            int offset { this->sizeY + 1 }; 
            int location { (position.y * this->sizeY) + this->sizeX };

            return location - offset;
        }

        // Takes in a raw location in the array and returns a position
        Position getPositionFromLocation(int location)
        {

            // calculate offset to start at (1,1)
            int offset { this->sizeY  + 1 };
            int new_location { location + offset };

            // Now calculate x and y
            int position_y { new_location / this->sizeY };
            int position_x { (new_location % this->sizeY) + 1 };

            return Position{position_x, position_y};
        }

    // Chessboard is stored as an array of size (x * y)
    private:
        // Store size of board for calculations
        const int sizeX {SizeX};
        const int sizeY {SizeY};

        // Board is a list of integers with each element representing a space on the board
        // Starts from bottom left and moves right, until it hits SizeX, and then moves up one Y
        // Integer is an ID for every piece
        std::array<int, SizeX * SizeY> board{};

        // A hashmap that holds the ID as a key and the actual Piece class as the value
        std::unordered_map<int, std::unique_ptr<Piece<SizeX, SizeY>>> id_map{};
            
        // A hashmap that alternatively holds every piece, so we can lookup positions from just the piece
        // Key is the ID of the piece, the value is the integer position of the piece
        std::unordered_map<int, int> piece_map{};

};
