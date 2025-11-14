#include <iostream>
#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "Toolbox.h"
using namespace std;

int gameLoop(sf::Event event);

int launch(){
    render();
    return 0;
}

void restart() {
    // Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
    // The new state should be a default game state (25x16 with 50 randomly placed mines).
    if (getDebugMode()) {
        toggleDebugMode();
    }
    Toolbox::getInstance().gameState = new GameState();
}

void render() {
    // Draws the all UI elements according to the current gameState and debug mode.
    while (Toolbox::getInstance().window.isOpen()) {
        Toolbox::getInstance().window.clear(sf::Color::White);
        sf::Event event;

        // event polling
        while (Toolbox::getInstance().window.pollEvent(event)) {
            gameLoop(event);
            if (event.type == sf::Event::Closed) {
                Toolbox::getInstance().window.close();
            }
        }

        // draw all tiles
        for (int i = 0; i < Toolbox::getInstance().gameState->getDimensions().x; i=i+32) {
            for (int j = 0; j < Toolbox::getInstance().gameState->getDimensions().y; j = j+32) {
                if (Toolbox::getInstance().gameState->getTile(i,j) != nullptr) {
                    Toolbox::getInstance().gameState->getTile(i,j)->draw();
                }
            }
        }

        // draw debug mode mines
        if (getDebugMode()) {
            for (sf::Sprite sprite:Toolbox::getInstance().debugSprites) {
                Toolbox::getInstance().window.draw(sprite);
            }
        }

        // draw buttons
        Toolbox::getInstance().window.draw(*Toolbox::getInstance().debugButton->getSprite());
        Toolbox::getInstance().window.draw(*Toolbox::getInstance().newGameButton->getSprite());
        Toolbox::getInstance().window.draw(*Toolbox::getInstance().testOneButton->getSprite());
        Toolbox::getInstance().window.draw(*Toolbox::getInstance().testTwoButton->getSprite());

        // draw flag count
        Toolbox::getInstance().displayDigits();

        Toolbox::getInstance().window.display();

    }
}

void toggleDebugMode() {
    // Flips the debug mode on/off. (Debug mode should initially be off/false.)

    if (getDebugMode()) { // turns debug mode off
        Toolbox::getInstance().debugSprites.clear();

    } else { // turns debug mode on
        // initialize variables
        vector<sf::Sprite> mineSprites;
        int mineCount = Toolbox::getInstance().gameState->getMineCount();
        // creates a vector of sprites equal to the number of bombs
        mineSprites = vector(mineCount, Toolbox::getInstance().debugMineSprite);
        float x = 0;
        float y = 0;
        int count = 0;

        // then loop through the board, wherever there's a mine set the next bomb sprite
        for(vector<int> row:Toolbox::getInstance().board) {
            for(int intTile:row) {
                if (intTile == -1) {
                    mineSprites[count].setPosition(x*32,y*32);
                    count++;
                }
                y++;
            }
            x++;
            y=0;
        }

        // load sprite vector into toolbox to be rendered
        Toolbox::getInstance().debugSprites = mineSprites;
    }
}

bool getDebugMode() {
    // Returns the true if debug mode is active, and false otherwise.
    if(Toolbox::getInstance().debugSprites.empty()) {
        return false;
    } else {
        return true;
    }
}


int gameLoop(sf::Event event) {
    // Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game.
    GameState* game = Toolbox::getInstance().gameState;

    int gameX = game->getDimensions().x;
    int gameY = game->getDimensions().y;

    if (event.type == sf::Event::MouseButtonReleased) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        // if the click is within the board, click the respective tile
        if (x < gameX && y < gameY) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                game->getTile(x, y)->onClickLeft();
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                game->getTile(x, y)->onClickRight();
            }
        }

        // test for other button clicks
        if (x > gameX - 428 && x < gameX - 364 && y < gameY + 64 && y > gameY) {
            Toolbox::getInstance().newGameButton->onClick();
        } else if (x > gameX-300 && x < gameX-236 && y <gameY+64 && y > gameY) {
            Toolbox::getInstance().debugButton->onClick();
        } else if (x > gameX-236 && x < gameX-172 && y < gameY+64 && y > gameY) {
            Toolbox::getInstance().testOneButton->onClick();
        } else if (x > gameX-172 && x < gameX-108 && y < gameY+64 && y > gameY) {
            Toolbox::getInstance().testTwoButton->onClick();
        }
    }

    // updates the new game button with the proper sprite based on gamestate
    if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::PLAYING) {
        Toolbox::getInstance().newGameButton->setSprite(&Toolbox::getInstance().newGameSprite);
    } else if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::LOSS) {
        Toolbox::getInstance().newGameButton->setSprite(&Toolbox::getInstance().gameLostSprite);
    } else if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::WIN) {
        Toolbox::getInstance().newGameButton->setSprite(&Toolbox::getInstance().gameWonSprite);
    }


    return 0;
}

int main() { return launch(); }
