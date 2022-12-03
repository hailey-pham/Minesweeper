//
// Created by Hailey on 11/27/2022.
//

#ifndef PROJECT_4_BUTTON_H
#define PROJECT_4_BUTTON_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Button {
public:
    Button(sf::Vector2f _position, function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
private:
    sf::Sprite* sprite;
    sf::Vector2f position;
    function<void(void)> whenClicked;
};


#endif //PROJECT_4_BUTTON_H
