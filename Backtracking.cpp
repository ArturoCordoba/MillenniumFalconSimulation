//
// Created by arturocv on 08/10/17.
//

#include "Backtracking.h"

LinkedList<BtkMatrixNode<int>*>* Backtracking::searchSolution(BtkMatrixNode<int> *start) {
    LinkedList<BtkMatrixNode<int>*>* path = new LinkedList<BtkMatrixNode<int>*>(); //Se crea la lista que almacena el camino
    searchSolution(start, path);

    return path;
}

BtkMatrixNode<int> * Backtracking::searchSolution(BtkMatrixNode<int> *current, LinkedList<BtkMatrixNode<int>*>* path) {
    path->insertAtEnd(current); //Se inserta el nodo actual en el camino que se esta siguiendo
    BtkMatrixNode<int>* node = nullptr;

    if(current->getData() == 2){ //Caso en el que se ha llegado a la linea de meta
        return current;
    }

    //Se busca una solucion a traves del nodo derecho
    if(current->getRigth() != nullptr) {//Se verifica que el nodo derecho no sea nulo

        if (current->getRigth()->getData() != 1 && path->containsElement(current->getRigth()) == false) { //Se verifica que el nodo derecho no sea un obstaculo y que no este visitado
            node = searchSolution(current->getRigth(), path); //Se realiza la busqueda con el nodo derecho

            if (node != nullptr){ //El nodo derecho lleva a una solucion
                return node;
            }
        }
    }

    //Se busca una solucion a traves del nodo superior
    if(current->getUp() != nullptr) {//Se verifica que el nodo superior no sea nulo

        if (current->getUp()->getData() != 1 && path->containsElement(current->getUp()) == false) { //Se verifica que el nodo superior no sea un obstaculo y que no este visitado
            node = searchSolution(current->getUp(), path); //Se realiza la busqueda con el nodo superior

            if (node != nullptr){ //El nodo superior lleva a una solucion
                return node;
            }
        }
    }

    //Se busca una solucion a traves del nodo inferior
    if(current->getDown() != nullptr) {//Se verifica que el nodo inferior no sea nulo

        if (current->getDown()->getData() != 1 && path->containsElement(current->getDown()) == false) { //Se verifica que el nodo inferior no sea un obstaculo y que no este visitado
            node = searchSolution(current->getDown(), path); //Se realiza la busqueda con el nodo inferior

            if (node != nullptr){ //El nodo inferior lleva a una solucion
                return node;
            }
        }
    }

    //Se busca una solucion a traves del nodo izquierdo
    if(current->getLeft() != nullptr) {//Se verifica que el nodo izquierdo no sea nulo

        if (current->getLeft()->getData() != 1 && path->containsElement(current->getLeft()) == false) { //Se verifica que el nodo izquierdo no sea un obstaculo y que no este visitado
            node = searchSolution(current->getLeft(), path); //Se realiza la busqueda con el nodo izquierdo

            if (node != nullptr){ //El nodo izquierdo lleva a una solucion
                return node;
            }
        }
    }

    path->deleteElement2(current); //Se elimina el nodo actual del camino
    return nullptr; //No se ha encontrado una solucion

}