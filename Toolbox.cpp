#include "Toolbox.h"
#include "Minesweeper.h"
#include <functional>
#include <cstdlib>
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

    int x = gameState->getDimensions().x;
    int y = gameState->getDimensions().y;

    // Reveals mines in debug mode
    debugButton = new Button(sf::Vector2f(x-300,y), toggleDebugMode);

    debugTexture.loadFromFile("../images/debug.png");
    debugSprite.setTexture(debugTexture);
    debugSprite.setPosition(debugButton->getPosition());
    debugButton->setSprite(&debugSprite);

    // Resets / starts new game
    newGameButton = new Button(sf::Vector2f(x-428,y), restart);
    newGameTexture.loadFromFile("../images/face_happy.png");
    newGameSprite.setTexture(newGameTexture);
    newGameSprite.setPosition(newGameButton->getPosition());
    newGameButton->setSprite(&newGameSprite);

    // loads sprite for game lost
    gameLostTexture.loadFromFile("../images/face_lose.png");
    gameLostSprite.setTexture(gameLostTexture);
    gameLostSprite.setPosition(newGameButton->getPosition());

    // loads sprite for game won
    gameWonTexture.loadFromFile("../images/face_win.png");
    gameWonSprite.setTexture(gameWonTexture);
    gameWonSprite.setPosition(newGameButton->getPosition());


    // Loads test board #1
    testOneButton = new Button(sf::Vector2f(x-236,y), testButtonOne);
    testOneTexture.loadFromFile("../images/test_1.png");
    testOneSprite.setTexture(testOneTexture);
    testOneSprite.setPosition(testOneButton->getPosition());
    testOneButton->setSprite(&testOneSprite);

    // Loads test board #2
    testTwoButton = new Button(sf::Vector2f(x-172,y), testButtonTwo);
    testTwoTexture.loadFromFile("../images/test_2.png");
    testTwoSprite.setTexture(testTwoTexture);
    testTwoSprite.setPosition(testTwoButton->getPosition());
    testTwoButton->setSprite(&testTwoSprite);

    // load sprites for debug textures
    debugMineTexture.loadFromFile("../images/mine.png");
    debugMineSprite.setTexture(debugMineTexture);

    // loads texture for digits
    digitTexture.loadFromFile("../images/digits.png");
    digitSprites = vector(4, sf::Sprite(digitTexture)); // vector of sprites to hold textures
    for (int i = 0; i < 4; i++) {
        digitSprites[i].setTexture(digitTexture); // set each texture
    }
    displayDigits();
}

void Toolbox::testButtonOne() { // loads test board 1
    // when resetting a game, if debug mode is on, turn it off
    if (getDebugMode()) {
        toggleDebugMode();
    }
    Toolbox::getInstance().gameState = new GameState("../boards/testboard1.brd");
}

void Toolbox::testButtonTwo() { // loads test board 2
    // when resetting a game, if debug mode is on, turn it off
    if (getDebugMode()) {
        toggleDebugMode();
    }
    Toolbox::getInstance().gameState = new GameState("../boards/testboard2.brd");
}

void Toolbox::displayDigits() {  // draws the flag count at the bottom of the board
    int mineCountByFlags = gameState->getMineCount() - gameState->getFlagCount();

    vector<int> digits;
    digits = vector(3, 0);

    digits[2] = abs(mineCountByFlags%10); // ones place
    digits[1] = abs((mineCountByFlags%100-digits[0])/10); // tens place
    digits[0] = abs((mineCountByFlags%1000-mineCountByFlags%100)/100); // hundreds place

    if (mineCountByFlags < 0) { // for negative numbers
        digitSprites[0].setTextureRect(sf::Rect(21*10,0,21,32));
        if (digits[0] == 0) { // if the number is negative and has a leading 0, don't show the leading 0
            digitSprites[1].setTextureRect(sf::Rect(21*digits[1],0,21,32));
            digitSprites[2].setTextureRect(sf::Rect(21*digits[2],0,21,32));
        } else { // else display them all
            digitSprites[1].setTextureRect(sf::Rect(21*digits[0],0,21,32));
            digitSprites[2].setTextureRect(sf::Rect(21*digits[1],0,21,32));
            digitSprites[3].setTextureRect(sf::Rect(21*digits[2],0,21,32));
        }
    } else { // for positive numbers
        digitSprites[0].setTextureRect(sf::Rect(21*digits[0],0,21,32));
        digitSprites[1].setTextureRect(sf::Rect(21*digits[1],0,21,32));
        digitSprites[2].setTextureRect(sf::Rect(21*digits[2],0,21,32));
        digitSprites[3].setTextureRect(sf::Rect(0,0,0,0));

    }

    for (int i = 0; i < 4; i++) {
        digitSprites[i].setPosition(sf::Vector2f(i*21,gameState->getDimensions().y)); // set position of sprites
    }

    // draw sprites
    window.draw(digitSprites[0]);
    window.draw(digitSprites[1]);
    window.draw(digitSprites[2]);
    window.draw(digitSprites[3]);
}