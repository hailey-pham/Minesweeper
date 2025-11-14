#ifndef PROJECT_4_MINESWEEPER_H
#define PROJECT_4_MINESWEEPER_H

#ifndef LAUNCH
#define LAUNCH
    int launch();
#endif

#ifndef RESTART
#define RESTART
    void restart();
#endif

#ifndef RENDER
#define RENDER
    void render();
#endif

#ifndef TOGGLEDEBUGMODE
#define TOGGLEDEBUGMODE
    void toggleDebugMode();
#endif

#ifndef GETDEBUGMODE
#define GETDEBUGMODE
    bool getDebugMode();
#endif




class Minesweeper {
public:
    int gameLoop(sf::Event event);
    int main();
};


#endif //PROJECT_4_MINESWEEPER_H
