#ifndef PROJECT_4_TILE_H
#define PROJECT_4_TILE_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Tile {
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();

protected:
    void revealNeighbors();

private:
    sf::Vector2f tilePosition;
    State state;

    sf::Texture revealedTexture;
    sf::Texture hiddenTexture;
    sf::Texture flaggedTexture;
    sf::Texture explodedTexture;
    sf::Texture emptyTexture;

    sf::Sprite sprite;
    sf::Sprite overlay;
};


#endif //PROJECT_4_TILE_H
