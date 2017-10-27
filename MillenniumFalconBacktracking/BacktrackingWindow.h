//
// Created by arturocv on 26/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_BACKTRACKINGWINDOW_H
#define MILLENNIUMFALCONSIMULATION_BACKTRACKINGWINDOW_H


#include<stdlib.h>
#include<time.h>
#include "../Asteroid.h"
#include "../DataStructures/LinkedList.h"
#include "../MillenniumFalcon.h"
#include "../DataStructures/BtkMatrix.h"

class BacktrackingWindow {
public:
    static int getXSize();

    static int getYSize();

    void render();

    void createMatrix(int maxAsteroids);

private:
    static int xSize;
    static int ySize;

    int iteration = 0;

    BtkMatrix<int>* matrix;

    Node<BtkMatrixNode<int>*>* current;

    MillenniumFalcon* millenniumFalcon;

    LinkedList<Asteroid*> asteroidList;

    void moveShip();


};


#endif //MILLENNIUMFALCONSIMULATION_BACKTRACKINGWINDOW_H
