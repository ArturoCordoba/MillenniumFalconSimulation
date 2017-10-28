//
// Created by arturocv on 26/10/17.
//

#include "Explosion.h"

Explosion::Explosion(int x, int y) {
    texture.loadFromFile("resources/explosion.png"); //Se carga la textura
    sprite = new sf::Sprite();
    sprite->setTexture(texture); //Se le coloca la textura al sprite
    sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite->setPosition(x, y); //Se coloca en la posicion ingresada
    Explosion::xMov = 0;
    Explosion::yMov = 0;
}

Explosion::~Explosion() {
    delete &texture;
    delete sprite;
    delete &left, &right, &bottom, &top;
    delete &xMov, &yMov;
    delete &lives;
}