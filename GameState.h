#ifndef PROJECT_4_GAMESTATE_H
#define PROJECT_4_GAMESTATE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tile.h"
using namespace std;

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);

private:
    vector<vector<Tile*>> intToTile(vector<vector<int>> _board);
    PlayStatus playstatus;
    vector<vector<int>> board;
    vector<vector<Tile*>> tileBoard;
    int flagCount;
    int mineCount;
    int xCount;
    int yCount;
};


#endif //PROJECT_4_GAMESTATE_H
