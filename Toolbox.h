#ifndef PROJECT_4_TOOLBOX_H
#define PROJECT_4_TOOLBOX_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
using namespace std;

class Toolbox {
public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState;    // Primary game state representation
    Button* debugButton;     // Reveals mines in debug mode
    Button* newGameButton;   // Resets / starts new game
    Button* testButton1;     // Loads test board #1
    Button* testButton2;     // Loads test board #2

    static Toolbox& getInstance() { return toolbox; };

    // Singleton implementation
    Toolbox(Toolbox &other) = delete;
    void operator=(const Toolbox &) = delete;

    void newGame();
    void testButton();
    void detectButtonPress();

private:
    Toolbox();
    static Toolbox toolbox;
};


#endif //PROJECT_4_TOOLBOX_H
