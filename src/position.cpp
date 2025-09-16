#include "position.hpp"

Position::Position() {
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position::~Position() {

}

Position Position::operator+(const Position& other) const {
    return Position(this->x + other.x, this->y + other.y);
}
