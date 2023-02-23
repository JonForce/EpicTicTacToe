#pragma once
#include <string>

class Board {

    private:
        int width, height, countToWin;
        
    public:
        enum Tile {
            X, O, EMPTY
        };

        enum Winner {
            TEAM_X, TEAM_O, NO_ONE
        };

        Tile* board;

        Board(int width, int height, int countToWin);
        ~Board();

        char tileToChar(Tile tile);
        void println(std::string text);
        void print();
        void reset();
        Tile get(int location);
        Tile get(int x, int y);
        void set(int x, int y, Tile value);
        void set(int location, Tile value);
        
        /* Place a tile at a location and return a winner if there is one. */
        Winner placeTile(int location, Tile tile);

        int countInDirection(int startX, int startY, int dirX, int dirY, Tile tile);
};