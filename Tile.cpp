#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Toolbox.h"
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

Tile::Tile(sf::Vector2f position) {
    // Constructs a new tile object at the designated _position.
    tilePosition = position;
    state = HIDDEN;

    revealedTexture.loadFromFile("../images/tile_revealed.png");
    hiddenTexture.loadFromFile("../images/tile_hidden.png");
    flaggedTexture.loadFromFile("../images/flag.png");
    explodedTexture.loadFromFile("../images/mine.png");
    emptyTexture.create(32,32);

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

std::array<Tile*, 8>& Tile::getNeighbors() {
    // Returns pointer to array of Tile pointers (see Figure 2 for ordering).
    std::array<Tile*, 8> neighbors;
    neighbors[0] = Toolbox::getInstance().gameState->getTile(tilePosition.x-32,tilePosition.y-32);
    neighbors[1] = Toolbox::getInstance().gameState->getTile(tilePosition.x,tilePosition.y-32);
    neighbors[2] = Toolbox::getInstance().gameState->getTile(tilePosition.x+32,tilePosition.y-32);

    neighbors[3] = Toolbox::getInstance().gameState->getTile(tilePosition.x-32,tilePosition.y);
    neighbors[4] = Toolbox::getInstance().gameState->getTile(tilePosition.x+32,tilePosition.y);

    neighbors[5] = Toolbox::getInstance().gameState->getTile(tilePosition.x-32,tilePosition.y+32);
    neighbors[6] = Toolbox::getInstance().gameState->getTile(tilePosition.x,tilePosition.y+32);
    neighbors[7] = Toolbox::getInstance().gameState->getTile(tilePosition.x+32,tilePosition.y+32);

    return neighbors;
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
    } else if (state == EXPLODED) {
        sprite.setTexture(revealedTexture);
        overlay.setTexture(explodedTexture);
    }
}

void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    // Populates / replaces the neighboring tile container.

}

void Tile::onClickLeft() {
    // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.
    if (state != FLAGGED) {
        state = REVEALED;
        sprite.setTexture(revealedTexture);
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

    if (state == FLAGGED) {

    } else if (state == HIDDEN) {

    } else if (state == REVEALED) {

    } else if (state == EXPLODED) {

    }
}