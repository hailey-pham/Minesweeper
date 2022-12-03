#include <iostream>
#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "Toolbox.h"
using namespace std;

void render();
int launch();
void restart();
void toggleDebugMode();
bool getDebugMode();
int gameLoop(sf::Event event);

int launch() {
    // This method is invoked directly by main() and is responsible for the game’s launch. It should be possible to
    // directly invoke this function after including the submitted source and header files in the test suite.
    //Toolbox::getInstance();
    render();

//    sf::RenderWindow window(sf::VideoMode(800,600),"P4 - Minesweeper, Hailey Pham");


// TESTING

//    cout << "TESTING START" << endl;
//    while (window.isOpen()) {
//        sf::Event event;
//
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                cout << "CLOSING" << endl;
//                window.close();
//            }
//        }
//
//        window.display();
//    }
//    cout << "TESTING END" << endl;

    // TESTING

    return 0;
}

void restart() {
    // Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
    // The new state should be a default game state (25x16 with 50 randomly placed mines).
   // Toolbox::getInstance().gameState = new GameState();
}

void render() {
    // Draws the all UI elements according to the current gameState and debug mode.
    while (Toolbox::getInstance().window.isOpen()) {
        sf::Event event;

        while (Toolbox::getInstance().window.pollEvent(event)) {
            gameLoop(event);
            if (event.type == sf::Event::Closed) {
                Toolbox::getInstance().window.close();
            }
        }

        for (int i = 0; i < Toolbox::getInstance().window.getSize().x; i=i+32) {
            for (int j = 0; j < Toolbox::getInstance().window.getSize().y-96; j = j+32) {
                if (Toolbox::getInstance().gameState->getTile(i,j) != nullptr) {
                    Toolbox::getInstance().gameState->getTile(i,j)->draw();
                }
            }

        }

        //cout << "CHECKPOINT" << endl;
        //cout << Toolbox::getInstance().window.getSize().y << endl;

//        for (int i = 0; i < Toolbox::getInstance().window.getSize().y; i=i+32) {
//            cout << i << endl;
//            Toolbox::getInstance().gameState->getTile(0,i)->draw();
//        }

//        for (int i = 0; i < Toolbox::getInstance().window.getSize().x; i++) {
//            Toolbox::getInstance().gameState->getTile(i,32)->draw();
//        }

        Toolbox::getInstance().window.display();

    }
}

//void toggleDebugMode() {
//    // Flips the debug mode on/off. (Debug mode should initially be off/false.)
//}
//
//bool getDebugMode() {
//    // Returns the true if debug mode is active, and false otherwise.
//}
//

int gameLoop(sf::Event event) {
    // Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game.
    GameState* game = Toolbox::getInstance().gameState;
    int x;
    int y;

    // ISSUES:
    // - A TILE CAN BE REVEALED THEN FLAGGED TO UNREVEAL IT
    // - NEED A WAY TO TOGGLE FLAG
    if (event.type == sf::Event::MouseButtonPressed) {
        x = event.mouseButton.x;
        y = event.mouseButton.y;
        if (event.mouseButton.button == sf::Mouse::Left) {
            //game->getTile(x,y)->setState(Tile::REVEALED);
            game->getTile(x,y)->onClickLeft();
        } else if (event.mouseButton.button == sf::Mouse::Right) {
//            if (game->getTile(x,y)->getState() == Tile::FLAGGED) {
//                game->getTile(x,y)->setState(Tile::HIDDEN);
//            } else if (game->getTile(x,y)->getState() == Tile::HIDDEN) {
//                game->getTile(x,y)->setState(Tile::FLAGGED);
//            }
            game->getTile(x,y)->onClickRight();
        }
    }

    return 0;
}



int main() { return launch(); }
