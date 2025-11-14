#ifndef PROJECT_4_TOOLBOX_H
#define PROJECT_4_TOOLBOX_H
#include <functional>
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
    Button* testOneButton;     // Loads test board #1
    Button* testTwoButton;     // Loads test board #2

    static Toolbox& getInstance() { return toolbox; };

    static void newGame();
    static void testButtonOne();
    static void testButtonTwo();

    vector<vector<int>> board;

    // sprites and textures
    vector<sf::Sprite> debugSprites;
    sf::Texture debugMineTexture;
    sf::Sprite debugMineSprite;
    sf::Sprite newGameSprite;
    sf::Sprite gameLostSprite;
    sf::Sprite gameWonSprite;

    void displayDigits();

    // Singleton implementation
    Toolbox(Toolbox &other) = delete;
    void operator=(const Toolbox &) = delete;

private:
    Toolbox();
    static Toolbox toolbox;

    // sprites and textures
    sf::Texture newGameTexture;
    sf::Texture gameLostTexture;
    sf::Texture gameWonTexture;
    sf::Texture debugTexture;
    sf::Sprite debugSprite;
    sf::Texture testOneTexture;
    sf::Sprite testOneSprite;
    sf::Texture testTwoTexture;
    sf::Sprite testTwoSprite;
    sf::Texture digitTexture;
    vector<sf::Sprite> digitSprites;
};


#endif //PROJECT_4_TOOLBOX_H
