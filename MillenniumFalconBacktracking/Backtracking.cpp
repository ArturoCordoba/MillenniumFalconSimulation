//
// Created by arturocv on 08/10/17.
//

#include "Backtracking.h"

/// Metodo para buscar una salida del laberinto
/// \param start Nodo inicial del recorrido
/// \return Una lista con el camino
LinkedList<BtkMatrixNode<int>*>* Backtracking::searchSolution(BtkMatrixNode<int> *start) {
    LinkedList<BtkMatrixNode<int>*>* path = new LinkedList<BtkMatrixNode<int>*>(); //Se crea la lista que almacena el camino
    LinkedList<BtkMatrixNode<int>*>* visitedNodes = new LinkedList<BtkMatrixNode<int>*>(); //Se crea la lista que almacena los nodos visitados
    searchSolution(start, path, visitedNodes); //Se realiza la busqueda

    return path;
}

/// Metodo para intentar cada posible camino en una matriz hasta que se encuentre uno que lleve a la salida
/// \param current Nodo actual en el recorrido
/// \param path Lista que guarda los nodos del camino final
/// \param visitedNodes Lista que guarda los nodos visitados
/// \return Siguiente nodo en el camino, nullptr si el camino que se siguio no es valido
BtkMatrixNode<int> * Backtracking::searchSolution(BtkMatrixNode<int> *current, LinkedList<BtkMatrixNode<int>*>* path, LinkedList<BtkMatrixNode<int>*>* visitedNodes) {
    path->insertAtEnd(current); //Se inserta el nodo actual en el camino que se esta siguiendo
    visitedNodes->insertAtFirst(current); //Se inserta el nodo actual en la lista de nodos visitados
    BtkMatrixNode<int>* node = nullptr;

    if(current->getData() == 2){ //Caso en el que se ha llegado a la linea de meta
        return current;
    }

    //Se busca una solucion a traves del nodo derecho
    if(current->getRigth() != nullptr) {//Se verifica que el nodo derecho no sea nulo

        if (current->getRigth()->getData() != 1 && visitedNodes->containsElement(current->getRigth()) == false) { //Se verifica que el nodo derecho no sea un obstaculo y que no este visitado
            node = searchSolution(current->getRigth(), path, visitedNodes); //Se realiza la busqueda con el nodo derecho

            if (node != nullptr){ //El nodo derecho lleva a una solucion
                return node;
            }
        }
    }

    //Se busca una solucion a traves del nodo inferior
    if(current->getDown() != nullptr) {//Se verifica que el nodo inferior no sea nulo

        if (current->getDown()->getData() != 1 && visitedNodes->containsElement(current->getDown()) == false) { //Se verifica que el nodo inferior no sea un obstaculo y que no este visitado
            node = searchSolution(current->getDown(), path, visitedNodes); //Se realiza la busqueda con el nodo inferior

            if (node != nullptr){ //El nodo inferior lleva a una solucion
                return node;
            }
        }
    }

    //Se busca una solucion a traves del nodo superior
    if(current->getUp() != nullptr) {//Se verifica que el nodo superior no sea nulo

        if (current->getUp()->getData() != 1 && visitedNodes->containsElement(current->getUp()) == false) { //Se verifica que el nodo superior no sea un obstaculo y que no este visitado
            node = searchSolution(current->getUp(), path, visitedNodes); //Se realiza la busqueda con el nodo superior

            if (node != nullptr){ //El nodo superior lleva a una solucion
                return node;
            }
        }
    }

    //Se busca una solucion a traves del nodo izquierdo
    if(current->getLeft() != nullptr) {//Se verifica que el nodo izquierdo no sea nulo

        if (current->getLeft()->getData() != 1 && visitedNodes->containsElement(current->getLeft()) == false) { //Se verifica que el nodo izquierdo no sea un obstaculo y que no este visitado
            node = searchSolution(current->getLeft(), path, visitedNodes); //Se realiza la busqueda con el nodo izquierdo

            if (node != nullptr){ //El nodo izquierdo lleva a una solucion
                return node;
            }
        }
    }

    path->deleteElement2(current); //Se elimina el nodo actual del camino
    return nullptr; //No se ha encontrado una solucion
}