#include <iostream>
#include <string>
#include "Board.h"

Board::Board(int width, int height, int countToWin) {
    this->width = width;
    this->height = height;
    this->countToWin = countToWin;
    board = new Tile[width * height];
}

Board::~Board() {
    delete board;
}

char Board::tileToChar(Tile tile) {
    return
        tile == X ? 'X' :
        tile == O ? 'O' :
        ' ';
}

void Board::println(std::string text) {
    std::cout << text << std::endl;
}

void Board::print() {
    println("    Board");
    println("----------------");
    for (int j = 0; j < height; j++) {
        std::cout << " | ";
        for (int i = 0; i < width; i++) {
            std::cout << tileToChar(get(i, j)) << " | ";
        }
        std::cout << std::endl;
    }
}

void Board::reset() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            set(i, j, EMPTY);
        }
    }
}

int Board::countInDirection(int startX, int startY, int dirX, int dirY, Tile tile) {
    if (startX + dirX < width && startY + dirY < height &&
            startX + dirX >= 0 && startY + dirY >= 0) {

        startX += dirX;
        startY += dirY;
        if (get(startX, startY) == tile) {
            return 1 + countInDirection(startX, startY, dirX, dirY, tile);
        }
    }
    
    return 0;
}

Board::Winner Board::placeTile(int location, Tile tile) {
    // Location here is a user input, so assume the locations are numbered starting from 1.
    // Players prefer counting starting from 1, not 0.
    location -= 1;
    int x = location % width;
    int y = location / width;

    set(x, y, tile);

    // Check to see if there are n in a row in either direction starting from x, y.

    // Up to the right.
    int inARowUR = countInDirection(x, y, 1, 1, tile) + countInDirection(x, y, -1, -1, tile);
    // Down and to the right
    int inARowDR = countInDirection(x, y, -1, 1, tile) + countInDirection(x, y, 1, -1, tile);
    // Right left
    int inARowRL = countInDirection(x, y, 1, 0, tile) + countInDirection(x, y, -1, 0, tile);
    // Up down
    int inARowUD = countInDirection(x, y, 0, 1, tile) + countInDirection(x, y, 0, -1, tile);

    // We add one because the current position always counts towards us winning.
    int inARow = std::max(std::max(inARowUR, inARowDR), std::max(inARowRL, inARowUD)) + 1;
    
    if (inARow >= countToWin) {
        if (tile == X) return TEAM_X;
        else return TEAM_O;
    }
    
    return NO_ONE;
}

Board::Tile Board::get(int x, int y) {
    return get(x + y * width);
}

void Board::set(int x, int y, Board::Tile value) {
    board[x + y * width] = value;
}

Board::Tile Board::get(int location) {
    return board[location];
}

void Board::set(int location, Board::Tile value) {
    board[location] = value;
}