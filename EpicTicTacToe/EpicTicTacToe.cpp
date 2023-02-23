#include <iostream>
#include <string>
#include "Board.h"
#include "Move.h"

void printWelcome() {
    std::cout << "~Epic Tic Tac Toe~" << std::endl;
    std::cout << "AN ADRENALINE FILLED TIC TAC EXPERIENCE" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

Board* configureBoard() {
    int width, height, countToWin;

    std::cout << "Enter board width : ";
    std::cin >> width;
    std::cout << std::endl << "Enter board height : ";
    std::cin >> height;
    std::cout << std::endl << "Enter count to win : ";
    std::cin >> countToWin;
    std::cout << std::endl;

    std::cout << "Postions are labeled 1 through " << width * height << std::endl;
    std::cout << "Enter -1 to undo a move " << std::endl << std::endl;
    Board* board = new Board(width, height, countToWin);
    board->reset();
    return board;
}

void playGame(Board* board) {
    board->print();

    Move* moves = NULL;
    Board::Tile currentTeam = Board::Tile::X;
    while (true) {
        int input;
        std::cout << "(" << board->tileToChar(currentTeam) << ") Enter a position : " << std::endl;
        std::cin >> input;

        // Do an undo.
        if (input == -1) {
            if (moves == NULL) {
                std::cout << "Can't undo!" << std::endl;
                continue;
            }
            board->set(moves->location, Board::Tile::EMPTY);
            // Toggle the team.
            currentTeam = (currentTeam == Board::Tile::X) ? Board::Tile::O : Board::Tile::X;

            Move* oldMove = moves;
            moves = moves->previous;
            delete oldMove;

            std::cout << "Undid move" << std::endl;
            board->print();

            continue;
        }

        // - 1 here because users enter starting at 1 and we count from 0.
        if (board->get(input - 1) != Board::Tile::EMPTY) {
            std::cout << "Space is not empty!" << std::endl;
            continue;
        }

        Board::Winner result = board->placeTile(input, currentTeam);
        if (result == Board::Winner::TEAM_X) {
            std::cout << "Team X wins" << std::endl;
            break;
        }
        else if (result == Board::Winner::TEAM_O) {
            std::cout << "Team Y wins" << std::endl;
            break;
        }

        // Store this move.
        Move* thisMove = new Move(moves, input - 1);
        moves = thisMove;

        // Swap which team is up.
        currentTeam = (currentTeam == Board::Tile::X) ? Board::Tile::O : Board::Tile::X;

        board->print();
        std::cout << std::endl;
    }
}

int main()
{
    printWelcome();
    Board* board = configureBoard();
    playGame(board);
    free(board);
}
