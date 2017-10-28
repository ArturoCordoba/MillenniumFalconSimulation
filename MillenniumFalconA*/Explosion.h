//
// Created by arturocv on 26/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_EXPLOSION_H
#define MILLENNIUMFALCONSIMULATION_EXPLOSION_H


#include "../Entity.h"

class Explosion : public Entity {
public:
    Explosion(int x, int y);

    ~Explosion();

    int currentX = 0;
};


#endif //MILLENNIUMFALCONSIMULATION_EXPLOSION_H
