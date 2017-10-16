//
// Created by fabian on 11/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_FALCON_H
#define MILLENNIUMFALCONSIMULATION_FALCON_H

#include <SFML/Graphics.hpp>
#include <iostream>

///Class of Falcon
class Falcon
{
public:
    sf::Sprite falcon;
    float bottom,left,right,top;

    ///Constructor method of falcon class
    Falcon(sf::Vector2f position, sf::Texture &texture)
    {
        falcon.setTexture(texture);
        falcon.setPosition(position);
        falcon.setTextureRect(sf::IntRect(0,0,32,32));
    }


    ///Method that updates the position of the object on screen
    void Update()
    {
        bottom = falcon.getPosition().y + falcon.getTextureRect().height;
        left = falcon.getPosition().x;
        right = falcon.getPosition().x + falcon.getTextureRect().width;
        top = falcon.getPosition().y;
    }

    /// Method that moves the object around the screen
    /// \param m
    void Move(char m)
    {
        switch(m)
        {
            case 'r':
                falcon.move(1.0f,0);
                break;
            case 'l':
                falcon.move(-1.0f,0);
                break;
            case 'u':
                falcon.move(0,-1.0f);
                break;
            case 'd':
                falcon.move(0,1.0f);
                break;
            default:
                std::cout << "No Movement" << std::endl;
                break;
        }
    }
};

#endif //MILLENNIUMFALCONSIMULATION_FALCON_H
