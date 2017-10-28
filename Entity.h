//
// Created by arturocv on 25/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_ENTITY_H
#define MILLENNIUMFALCONSIMULATION_ENTITY_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity {
public:
    Entity();

    sf::Sprite* getSprite();

    int getXMov();

    int getYMov();

    int getLives();

    void move();

    void update();

    bool checkCollision(Entity *entity);

    void correctPosition();

    void changeXDirection();

    void changeYDirection();

    void setXMov(int xMov);

    void setYMov(int yMov);

    void substractLive();

    int getLeft();

    int getRight();

    int getBottom();

    int getTop();

protected:
    sf::Texture texture;
    sf::Sprite* sprite;
    float left, right, bottom, top;
    float xMov, yMov;
    int lives;
};


#endif //MILLENNIUMFALCONSIMULATION_ENTITY_H
