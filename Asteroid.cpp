//
// Created by arturocv on 16/10/17.
//

#include "Asteroid.h"

Asteroid::Asteroid(int x, int y, float xMov, float yMov) {
    texture.loadFromFile("resources/asteroid.png"); //Se carga la textura
    sprite = new sf::Sprite();
    sprite->setTexture(texture); //Se le coloca la textura al sprite
    sprite->setTextureRect(sf::IntRect(0, 0, 60, 60));
    sprite->setPosition(x, y); //Se coloca en la posicion ingresada
    Asteroid::xMov = xMov;
    Asteroid::yMov = yMov;
    lives = 1; //Se le asigna la cantidad de vidas
}

Asteroid::~Asteroid() {
    delete &texture;
    delete sprite;
    delete &left, &right, &bottom, &top;
    delete &xMov, &yMov;
    delete &lives;
}
