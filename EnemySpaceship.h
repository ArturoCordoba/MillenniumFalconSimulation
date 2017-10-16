//
// Created by fabian on 15/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_ENEMYSPACESHIP_H
#define MILLENNIUMFALCONSIMULATION_ENEMYSPACESHIP_H

#include <SFML/Graphics.hpp>
#include <iostream>

///Class of Enemy Spaceship
class EnemySpaceship
{
    sf::Sprite enemy;
    float bottom,left,right,top;

    ///Constructor method of enemy spaceship class
    EnemySpaceship(sf::Vector2f position, sf::Texture &texture)
    {
        enemy.setTexture(texture);
        enemy.setTextureRect(sf::IntRect(0,0,32,32));
        enemy.setPosition(position);
    }

    ///Method that updates the position of the object on screen
    void Update()
    {
        bottom =  enemy.getPosition().y + enemy.getTextureRect().height;
        left = enemy.getPosition().x;
        right = enemy.getPosition().x + enemy.getTextureRect().width;
        top = enemy.getPosition().y;
    }

    ///Method that moves the object around the screen
    void Move(char m)
    {
        switch(m)
        {
            case 'r':
                enemy.move(1.0f,0);
                break;
            case 'l':
                enemy.move(-1.0f,0);
                break;
            case 'u':
                enemy.move(0,-1.0f);
                break;
            case 'd':
                enemy.move(0,1.0f);
                break;
            default:
                std::cout << "No Movement" << std::endl;
                break;
        }
    }
};

#endif //MILLENNIUMFALCONSIMULATION_ENEMYSPACESHIP_H
