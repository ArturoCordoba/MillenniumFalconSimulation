//
// Created by arturocv on 25/10/17.
//

#include "Entity.h"
#include "MillenniumFalconBacktracking/BacktrackingWindow.h"

Entity::Entity() {

}

sf::Sprite *Entity::getSprite() {
    return Entity::sprite;
}

int Entity::getXMov() {
    return Entity::xMov;
}

int Entity::getYMov() {
    return Entity::yMov;
}

int Entity::getLives() {
    return Entity::lives;
}

void Entity::move() {
    sprite->move(sf::Vector2f(xMov, yMov));
}

///Metodo para actualizar el BoxCollision de la entidad
void Entity::update() {
    if(sprite->getPosition().x < 0 || (sprite->getPosition().x > BacktrackingWindow::getXSize() - sprite->getTextureRect().width)){ //Si el sprite esta mas alla de los bordes laterales de la pantalla
        xMov *= -1; //Se multiplica por menos uno para que vaya en la direccion contraria
    }
    if(sprite->getPosition().y < 0 || (sprite->getPosition().y > BacktrackingWindow::getYSize() - sprite->getTextureRect().height)) //Si el sprite esta mas alla de los bordes verticales de la pantalla
        yMov *= -1; //Se multiplica por menos uno para que vaya en la direccion contraria

    bottom = sprite->getPosition().y + sprite->getTextureRect().height;
    left = sprite->getPosition().x;
    right = sprite->getPosition().x + sprite->getTextureRect().width;
    top = sprite->getPosition().y;
}

/// Metodo para verificar si la entidad a colisionado con otra
/// \param entity Entidad con la cual verificar
/// \return True si hay colision, false en caso contrario
bool Entity::checkCollision(Entity *entity) {
    if (right <= entity->left || left >= entity->right || top >= entity->bottom || bottom <= entity->top) {
        return false;
    }

    return true;
}

///Metodo para cambiar la direccion en x
void Entity::changeXDirection() {
    xMov *= -1;
}

///Metodo para cambiar la direccion en y
void Entity::changeYDirection() {
    yMov *= -1;
}

///Metodo para colocar una direccion en x
void Entity::setXMov(int xMov) {
    Entity::xMov = xMov;
}

///Metodo para colocar una direccion en y
void Entity::setYMov(int yMov) {
    Entity::yMov = yMov;
}

///Metodo para extraer una vida de la entidad
void Entity::substractLive() {
    lives -= 1;
}

///Metodo para corregir la posicion del sprite
void Entity::correctPosition() {
    int xPos = sprite->getPosition().x; //Se obtiene la posicion en x
    int correctionX = xPos % 60; //Se calcula la correccion
    int resultX = xPos;

    if(correctionX > 30){
        resultX = xPos + (60 - correctionX);
    } else{
        resultX = xPos - correctionX;
    }

    int yPos = sprite->getPosition().y; //Se obtiene la posicion en y
    int correctionY = yPos % 60; //Se calcula la correccion
    int resultY = yPos;

    if(correctionY > 30){
        resultY = yPos + (60 - correctionY);
    } else {
        resultY = yPos - correctionY;
    }

    sprite->setPosition(resultX, resultY); //Se coloca la posicion corregida

    update(); //Se actualizan las variables para colisiones
}

