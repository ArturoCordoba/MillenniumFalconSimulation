//
// Created by arturocv on 23/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_TIE_FIGHTER_H
#define MILLENNIUMFALCONSIMULATION_TIE_FIGHTER_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Entity.h"

class TIE_Fighter : public Entity {
public:
    TIE_Fighter(int x, int y, float xMov, float yMov);
private:
};


#endif //MILLENNIUMFALCONSIMULATION_TIE_FIGHTER_H
