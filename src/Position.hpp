#pragma once

/*
struct Position
{
    int x;
    int y;
}; */

class Position
{
    public:
        int x;
        int y;

        Position();
        Position(int x, int y);
        ~Position();

        Position operator+(const Position& other) const;
};

