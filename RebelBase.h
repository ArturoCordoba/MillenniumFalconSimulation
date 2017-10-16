//
// Created by fabian on 15/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_REBELBASE_H
#define MILLENNIUMFALCONSIMULATION_REBELBASE_H

#include <SFML/Graphics.hpp>
#include <iostream>

///Class of Rebel Base
class RebelBase {
public:
    sf::Sprite base;
    float bottom, left, right, top;

    ///Constructor method of rebel base class
    RebelBase(sf::Vector2f position, sf::Texture &texture)
    {
        base.setTexture(texture);
        base.setPosition(position);
        base.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    ///Method that updates the position of the object on screen
    void Update() {
        bottom = base.getPosition().y + base.getTextureRect().height;
        left = base.getPosition().x;
        right = base.getPosition().x + base.getTextureRect().width;
        top = base.getPosition().y;
    }
};

#endif //MILLENNIUMFALCONSIMULATION_REBELBASE_H
