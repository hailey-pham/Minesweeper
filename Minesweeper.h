#ifndef PROJECT_4_MINESWEEPER_H
#define PROJECT_4_MINESWEEPER_H


class Minesweeper {
    int launch();
    void restart();
    void render();
    void toggleDebugMode();
    bool getDebugMode();
    int gameLoop(sf::Event event);
    int main();
};


#endif //PROJECT_4_MINESWEEPER_H
