#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "GameState.h"
#include "Tile.h"
#include "Toolbox.h"
using namespace std;

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    // Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.
    flagCount = 0;
    mineCount = _numberOfMines;
    xCount = _dimensions.x;
    yCount = _dimensions.y;
    board = vector(xCount, vector<int>(yCount, 0)); // initialize 2d vector of 0s
    bool repeat = false;
    playstatus = PLAYING;

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

    // tile board stores a tile in a vector where each tile takes up one space
    tileBoard = intToTile(board);

    // stores the integer board in a 2d vector
    Toolbox::getInstance().board = generateFullBoard();
}

GameState::GameState(const char* filepath) {
    // Constructs a game state based on the size, mine placement, and mine number specified at filepath.

    // INITIALIZE VARIABLES
    ifstream boardFile;
    boardFile.open(filepath);
    xCount = 0;
    yCount = 0;
    mineCount = 0;
    flagCount = 0;
    playstatus = PLAYING;
    char tempChar;
    vector<int> row; // temporary vector to store ints

    if (boardFile.is_open()) {
        while (boardFile.get(tempChar)) {

            if (tempChar == '\n') {
                if(!row.empty()) {
                    yCount++;
                    board.push_back(row);
                    row.clear();
                }
            } else {
                if (yCount == 1) {
                    xCount++;
                }
                if (tempChar == '1') {
                    mineCount++;
                }

                row.push_back(int(tempChar) - 48); // -48 to convert from ascii to int
            }
        }
        if(!row.empty()) {
            yCount++;
            board.push_back(row);
            row.clear();
        }
    }
    // board is read on the wrong axis, so I manually flip the board
    board = flipBoard();
    tileBoard = intToTile(board); // create board of tile objects
    Toolbox::getInstance().board = generateFullBoard(); // load board with number values into toolbox

    boardFile.close();
}

vector<vector<Tile*>> GameState::intToTile(vector<vector<int>> _board) {
    tileBoard = vector(xCount, vector<Tile*>(yCount, 0));
    // takes 2d vector of integers and converts it to a 2d vector of tile objects
    for (int i = 0; i < xCount; i++) {
        for (int j = 0; j < yCount; j++) {
            tileBoard[i][j] = new Tile(sf::Vector2f(i*32,j*32)); // multiply by 32 to account for tile size
        }
    }

    return tileBoard;
}


int GameState::getFlagCount() {
    // Current count of the number of flags placed on the screen.
    flagCount = 0;
    for (int i = 0; i < xCount; i++) {
        for (int j = 0; j < yCount; j++) {
            if (getTile(i*32,j*32)->getState() == Tile::FLAGGED) {
                flagCount++;
            }
        }
    }

    return flagCount;

}

int GameState::getMineCount() {
    // Current count of the number of mines actually on the board.
    return mineCount;
}

Tile* GameState::getTile(int x, int y) {
    // Returns a pointer to the Tile at the specified coordinates, or nullptr if out o  f bounds.
    if (((x/32) >= xCount) || ((y/32) >= yCount) || (x < 0) || (y < 0)) {
        return nullptr;
    } else {
        // coordinate - (coordinate % [dimension of each tile])
        // ensures that even if the tile was not clicked in its origin, it will still return the correct tile

        return tileBoard[(x-(x%32))/32][(y-(y%32))/32]; // the tile board
    }
}

GameState::PlayStatus GameState::getPlayStatus() {
    // Returns the play status of the game.
    checkWinStatus(); // check status before returning

    return playstatus;
}

void GameState::setPlayStatus(GameState::PlayStatus _status) {
    // Sets the play status of the game.
    playstatus = _status;

    if (_status == LOSS) {
        for (int i = 0; i < xCount; i++) {
            for (int j = 0; j < yCount; j++) {
                getTile(i*32,j*32)->setState(Tile::REVEALED);
            }
        }
    }

}

sf::Vector2i GameState::getDimensions() {
    // returns dimensions of the board
    return sf::Vector2i(xCount*32,yCount*32);
}

// generates a representation of a board including bombs and numbers
vector<vector<int>> GameState::generateFullBoard() {
    vector<vector<int>> fullBoard = vector(xCount, vector<int>(yCount, 0));

    for (int i = 0; i < xCount; i++) {
        for (int j = 0; j < yCount; j++) {
            if (board[i][j] == 1) {
                fullBoard[i][j] = -1; // -1 = bomb

                // adds 1 to adjacent tiles if the tile exists, and it's not a bomb
                if(i-1 >= 0 && j-1 >= 0 && fullBoard[i-1][j-1] != -1) fullBoard[i-1][j-1]++;
                if(i-1 >= 0 && fullBoard[i-1][j] != -1) fullBoard[i-1][j]++;
                if(i-1 >= 0 && j+1 < yCount && fullBoard[i-1][j+1] != -1) fullBoard[i-1][j+1]++;

                if(j-1 >= 0 && fullBoard[i][j-1] != -1) fullBoard[i][j-1]++;
                if(j+1 < yCount && fullBoard[i][j+1] != -1) fullBoard[i][j+1]++;

                if(i+1 < xCount && j-1 >= 0 && fullBoard[i+1][j-1] != -1) fullBoard[i+1][j-1]++;
                if(i+1 < xCount && fullBoard[i+1][j] != -1) fullBoard[i+1][j]++;
                if(i+1 < xCount && j+1 < yCount && fullBoard[i+1][j+1] != -1) fullBoard[i+1][j+1]++;

            }
        }
    }

    return fullBoard;

}

vector<vector<int>> GameState::flipBoard() {
    // flips x and y axis of a 2d vector
    vector<vector<int>> flippedBoard;

    flippedBoard = vector(xCount, vector<int>(yCount, 0));

    for (int i = 0; i < yCount; i++) {
        for (int j = 0; j < xCount; j++) {
            flippedBoard[j][i] = board[i][j];
        }
    }

    return flippedBoard;
}


void GameState::checkWinStatus() {
    // if the amount of hidden/flagged tiles equals the amount of mines exactly, then the game has been won
    int hiddenTiles = 0;
    for (int i = 0; i < xCount; i++) {
        for (int j = 0; j < yCount; j++) {

            if (getTile(i*32,j*32)->getState() == Tile::HIDDEN || getTile(i*32,j*32)->getState() == Tile::FLAGGED) {
                hiddenTiles++;
            }

        }
    }


    if (mineCount - hiddenTiles == 0) {
        playstatus = WIN;
    }
}