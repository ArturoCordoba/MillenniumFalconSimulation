//
// Created by arturocv on 16/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_GAMEWINDOW_H
#define MILLENNIUMFALCONSIMULATION_GAMEWINDOW_H


#include <SFML/Graphics.hpp>
#include "../Asteroid.h"
#include "../DataStructures/LinkedList.h"
#include "TIE_Fighter.h"
#include "../MillenniumFalcon.h"
#include "Explosion.h"
#include "../DataStructures/PfdMatrix.h"


class PathfindingWindow {
public:
    static int getXSize();

    static int getYSize();

    static int getMaxAsteroids();

    void render();

private:
    static int xSize;
    static int ySize;
    static int maxAsteroids;

    PfdMatrix<int>* matrix;

    Node<PfdMatrixNode<int>*>* current;

    MillenniumFalcon* millenniumFalcon;

    LinkedList<Asteroid*> asteroidList;

    LinkedList<TIE_Fighter*> tieFightersList;

    LinkedList<Explosion*> explosionList;

    Asteroid* createAsteroid(int x, int y, float xMov, float yMov);

    TIE_Fighter* createTIEFighter(int x, int y, float xMov, float yMov);

    void createMap();

    void createMap1();

    void checkCollisions();

    void asteroidCollision(Asteroid* asteroid1, Asteroid* asteroid2);

    void updateMap();

    void moveMillenniumFalcon();
};


#endif //MILLENNIUMFALCONSIMULATION_GAMEWINDOW_H
