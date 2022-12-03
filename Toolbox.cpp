#include "Toolbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

Toolbox Toolbox::toolbox;

void newGame();
void testButton();


Toolbox::Toolbox() {
    // draw window
    window.create(sf::VideoMode(800,600),"P4 - Minesweeper, Hailey Pham");

    gameState = new GameState();
//    debugButton = new Button();     // Reveals mines in debug mode
//    newGameButton = new Button(sf::Vector2f(0,window.getSize()),newGame());   // Resets / starts new game
//    testButton1 = new Button();     // Loads test board #1
//    testButton2 = new Button();
}

//void Toolbox::newGame() {
//
//}
//
//void Toolbox::testButton() {
//
//}

//void Toolbox::detectButtonPress() {
//
//}