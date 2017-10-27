//
// Created by arturocv on 08/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_BACKTRACKING_H
#define MILLENNIUMFALCONSIMULATION_BACKTRACKING_H


#include "../DataStructures/BtkMatrixNode.h"
#include "../DataStructures/LinkedList.h"

class Backtracking {
public:
    static LinkedList<BtkMatrixNode<int>*>* searchSolution(BtkMatrixNode<int> *start);

private:
    static BtkMatrixNode<int> * searchSolution(BtkMatrixNode<int> *current, LinkedList<BtkMatrixNode<int>*>* path, LinkedList<BtkMatrixNode<int>*>* visitedNodes);

};


#endif //MILLENNIUMFALCONSIMULATION_BACKTRACKING_H
