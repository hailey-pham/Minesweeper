#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "Tile.h"
#include "Toolbox.h"

using namespace std;
namespace fs = std::filesystem;

Tile::Tile(sf::Vector2f position) {
    // Constructs a new tile object at the designated _position.
    tilePosition = position;
    state = HIDDEN;

    // loads all possible textures
    revealedTexture.loadFromFile("../images/tile_revealed.png");
    hiddenTexture.loadFromFile("../images/tile_hidden.png");
    flaggedTexture.loadFromFile("../images/flag.png");
    explodedTexture.loadFromFile("../images/mine.png");
    emptyTexture.create(32,32);

    // one sprite for the background and one for the overlay
    sprite.setPosition(position);
    overlay.setPosition(position);
    sprite.setTexture(hiddenTexture);
}

sf::Vector2f Tile::getLocation() {
    // Returns the position of this tile.
    return tilePosition;
}

Tile::State Tile::getState() {
    // Returns current state of this tile.
    return state;
}

array<Tile*, 8>& Tile::getNeighbors() {
    // Returns pointer to array of Tile pointers (see Figure 2 for ordering).
    int currentX = tilePosition.x;
    int currentY = tilePosition.y;

    Tile* zero = Toolbox::getInstance().gameState->getTile(currentX-32,currentY-32);
    Tile* one = Toolbox::getInstance().gameState->getTile(currentX,currentY-32);
    Tile* two = Toolbox::getInstance().gameState->getTile(currentX+32,currentY-32);

    Tile* three = Toolbox::getInstance().gameState->getTile(currentX-32,currentY);
    Tile* four = Toolbox::getInstance().gameState->getTile(currentX+32,currentY);

    Tile* five = Toolbox::getInstance().gameState->getTile(currentX-32,currentY+32);
    Tile* six = Toolbox::getInstance().gameState->getTile(currentX,currentY+32);
    Tile* seven = Toolbox::getInstance().gameState->getTile(currentX+32,currentY+32);

    // create a new array of the tiles
    array<Tile*, 8> neighbors =  {zero,one,two,three,four,five,six,seven};
    // create reference to array
    array<Tile *, 8>& newNeighbors = neighbors;

    return newNeighbors;
}

void Tile::setState(Tile::State _state) {
    // Sets the state of this tile. Should trigger other behaviors related to the state change (including visualization)
    state = _state;

    if (state == FLAGGED) {
        sprite.setTexture(hiddenTexture);
        overlay.setTexture(flaggedTexture);

    } else if (state == HIDDEN) {
        sprite.setTexture(hiddenTexture);
        overlay.setTexture(emptyTexture);

    } else if (state == REVEALED) {
        sprite.setTexture(revealedTexture);
        overlay.setTexture(emptyTexture);

        int currentTileValue = Toolbox::getInstance().board[tilePosition.x/32][tilePosition.y/32];

        if (1 <= currentTileValue && currentTileValue <= 8){
            // load an image based on the tile value
            string numberPath = "../images/number_"+to_string(currentTileValue) + ".png";
            tileTexture.loadFromFile(numberPath);
            overlay.setTexture(tileTexture);

        } else if (currentTileValue == 0) {
            // reveal neighbors
            revealNeighbors();
        } else if (currentTileValue == -1) {
            overlay.setTexture(explodedTexture);
        }

    } else if (state == EXPLODED) {
        sprite.setTexture(revealedTexture);
        overlay.setTexture(explodedTexture);

        // if a mine is exploded, set the game state to lost
        Toolbox::getInstance().gameState->setPlayStatus(GameState::LOSS);
    }
}

void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    // Populates / replaces the neighboring tile container.
    array<Tile*, 8> neighbors;
    neighbors = getNeighbors();

    neighbors[0] = _neighbors[0];
    neighbors[1] = _neighbors[1];
    neighbors[2] = _neighbors[2];
    neighbors[3] = _neighbors[3];
    neighbors[4] = _neighbors[4];
    neighbors[5] = _neighbors[5];
    neighbors[6] = _neighbors[6];
    neighbors[7] = _neighbors[7];
}

void Tile::onClickLeft() {
    // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.
    int currentTileValue = Toolbox::getInstance().board[tilePosition.x/32][tilePosition.y/32];

    string numberPath;
    if (state != FLAGGED && state != REVEALED) {
        if (currentTileValue == -1) {
            setState(EXPLODED);

        } else if (0 <= currentTileValue && currentTileValue <= 8){
            setState(REVEALED);
        }
    }
}

void Tile::onClickRight() {
    // Toggles this tile’s state between FLAGGED and HIDDEN.
    if (state == FLAGGED) {
        state = HIDDEN;
        sprite.setTexture(hiddenTexture);
        overlay.setTexture(emptyTexture);

    } else if (state == HIDDEN) {
        state = FLAGGED;
        sprite.setTexture(hiddenTexture);
        overlay.setTexture(flaggedTexture);

    }
}

void Tile::draw() {
    // Render this tile to the screen according to is state.
    Toolbox::getInstance().window.draw(sprite);
    Toolbox::getInstance().window.draw(overlay);
}

void Tile::revealNeighbors() {
    // Based on State and mine content of the tile neighbors, set their state to REVEALED.
    array<Tile*, 8> neighbors;
    neighbors = getNeighbors();

    for (int i = 0; i < 8; i++) {
        if (neighbors[i] != nullptr) {
            if (neighbors[i]->getState() != REVEALED) {
                neighbors[i]->onClickLeft();
            }
        }
    }

}
