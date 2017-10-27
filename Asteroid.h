//
// Created by arturocv on 16/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_DYNAMICASTEROID_H
#define MILLENNIUMFALCONSIMULATION_DYNAMICASTEROID_H


#include <SFML/Graphics.hpp>
#include "Entity.h"

class Asteroid : public Entity{
public:
    Asteroid(int x, int y, float xMov, float yMov);

    ~Asteroid();

private:
};


#endif //MILLENNIUMFALCONSIMULATION_DYNAMICASTEROID_H
