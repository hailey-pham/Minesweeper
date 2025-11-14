#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Minesweeper.h"
using namespace std;


Button::Button(sf::Vector2f _position, function<void(void)> _onClick) {
    // Constructs a new object at the specified _position which invokes the _onClick callback when clicked.
    position = _position;
    whenClicked = _onClick;
}

sf::Vector2f Button::getPosition() {
    // Returns the position of the button.
    return position;
}

sf::Sprite* Button::getSprite(){
    // Returns the current sprite of the button.
    return sprite;
}

void Button::setSprite(sf::Sprite* _sprite){
    // Sets this button’s visualization to the specified _sprite.
    sprite = _sprite;
}

void Button::onClick(){
    // Invokes the button’s callback method (usually called when clicked).
    whenClicked();
}

