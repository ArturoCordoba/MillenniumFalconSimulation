//
// Created by arturocv on 23/10/17.
//

#include "MillenniumFalcon.h"

MillenniumFalcon::MillenniumFalcon() {
    texture.loadFromFile("resources/millennium_falcon.png"); //Se carga la textura
    sprite = new sf::Sprite();
    sprite->setTexture(texture); //Se le coloca la textura al sprite
    sprite->setPosition(0, 0);
}