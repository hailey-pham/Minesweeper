#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Tile.h"
using namespace std;

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    // Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.
    flagCount = 0;
    mineCount = _numberOfMines;
    xCount = _dimensions.x;
    yCount = _dimensions.y;
    board = vector(xCount, vector<int>(yCount, 0)); // initialize 2d vector of 0s
    bool repeat = false;

    // randomly assign mines
    int randX;
    int randY;
    for (int i = 0; i < _numberOfMines; i++) {
        do {
            randX = int(rand() % xCount);
            randY = int(rand() % yCount);
            if (board[randX][randY] == 1) {
                repeat = true;
            } else {
                repeat = false;
                board[randX][randY] = 1;
            }
        } while (repeat == true);
    }

//
//  PRINT FOR TESTING PURPOSES
//
//    for (int i = 0; i < xCount; i++) {
//        for (int j = 0; j < yCount; j++) {
//            cout << board[i][j];
//        }
//        cout << endl;
//    }

    // tile board stores a tile in a vector where each tile takes up one space
    tileBoard = intToTile(board);

}

GameState::GameState(const char* filepath) {
    // Constructs a game state based on the size, mine placement, and mine number specified at filepath.
}

vector<vector<Tile*>> GameState::intToTile(vector<vector<int>> _board) {
    tileBoard = vector(xCount, vector<Tile*>(yCount, 0));
    // takes vector of integers and converts it to a vector of tiles
    for (int i = 0; i < xCount; i++) {
        for (int j = 0; j < yCount; j++) {
            tileBoard[i][j] = new Tile(sf::Vector2f(i*32,j*32));
        }
    }

    return tileBoard;
}


int GameState::getFlagCount() {
    // Current count of the number of flags placed on the screen.
    return flagCount;
}

int GameState::getMineCount() {
    // Current count of the number of mines actually on the board.
    return mineCount;
}

Tile* GameState::getTile(int x, int y) {
    // Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds.
    if (x/32 > xCount || y/32 > yCount) {
        return nullptr;
    } else {
        // coordinate - (coordinate % [dimension of each tile])
        // ensures that even if the tile was not clicked in its origin, it will still return the correct tile

        return tileBoard[(x-(x%32))/32][(y-(y%32))/32]; // the tile board

        //return tileBoard[x/32][y/32];
    }
}

GameState::PlayStatus GameState::getPlayStatus() {
    // Returns the play status of the game.
    return playstatus;
}

void GameState::setPlayStatus(GameState::PlayStatus _status) {
    // Sets the play status of the game.
    playstatus = _status;
}
