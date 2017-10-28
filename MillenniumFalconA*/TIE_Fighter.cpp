//
// Created by arturocv on 23/10/17.
//

#include "TIE_Fighter.h"

TIE_Fighter::TIE_Fighter(int x, int y, float xMov, float yMov) {
    texture.loadFromFile("resources/tie_fighter.png"); //Se carga la textura
    sprite = new sf::Sprite();
    sprite->setTexture(texture); //Se le coloca la textura al sprite
    sprite->setPosition(x, y); //Se coloca en la posicion ingresada
    TIE_Fighter::xMov = xMov;
    TIE_Fighter::yMov = yMov;
}