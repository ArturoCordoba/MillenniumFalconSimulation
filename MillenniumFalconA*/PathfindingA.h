//
// Created by arturocv on 11/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_A_PATHFINDING_H
#define MILLENNIUMFALCONSIMULATION_A_PATHFINDING_H

#include "../DataStructures/PfdMatrixNode.h"
#include "../DataStructures/PfdMatrix.h"
#include "../DataStructures/LinkedList.h"

template <class T>
class PathfindingA {
public:
    /// Metodo para encontrar la ruta mas corta entre dos nodos de una matriz
    /// \param matrix Matriz del problema
    /// \param xStart Coordenada en x del nodo de salida
    /// \param yStart Coordenada en y del nodo de salida
    /// \param xEnd Coordenada en x del nodo de llegada
    /// \param yEnd Coordenada en y del nodo de llegada
    /// \param straightMovement Valor del movimiento en horizontal/vertical
    /// \param diagonalMovement Valor del movimiento en diagonal
    /// \return LinkedList con el camino a seguir desde el nodo salida hasta el nodo de llegada
    static LinkedList<PfdMatrixNode<T>*>* calculatePath(PfdMatrix<T>* matrix, int xStart, int yStart, int xEnd, int yEnd, int straightMovement, int diagonalMovement) {
        cleanMatrix(matrix); //Se limpia el F de todos los nodos de la matriz
        calculateH(matrix, xEnd, yEnd); //Se calcula el H para cada nodo de la lista

        //Se crean la openlist y la close list
        LinkedList<PfdMatrixNode<T>*>* openList = new LinkedList<PfdMatrixNode<T> *>();
        LinkedList<PfdMatrixNode<T>*>* closeList = new LinkedList<PfdMatrixNode<T> *>();

        PfdMatrixNode<T> *end = matrix->getNode(xEnd, yEnd); //Se obtiene el nodo de llegada
        PfdMatrixNode<T> *current = matrix->getNode(xStart, yStart); //Se obtiene el nodo de salida

        openList->insertAtFirst(current);

        do {
            current = getMinOpenList(openList); //Se obtiene el nodo con el menor F de la openlist

            openList->deleteElement2(current); //Se elimina el current de la openlist
            closeList->insertAtEnd(current); //Se almacena el current en la closelist

            checkF(current, current->getUp(), end, straightMovement, openList, closeList); //Se verifica el nodo superior
            checkF(current, current->getDown(), end, straightMovement, openList, closeList); //Se verifica el nodo inferior
            checkF(current, current->getRigth(), end, straightMovement, openList, closeList); //Se verifica el nodo de la derecha
            checkF(current, current->getLeft(), end, straightMovement, openList, closeList); //Se verifica el nodo de la izquierda

            if(current->getUp() != nullptr){
                checkF(current, current->getUp()->getLeft(), end, diagonalMovement, openList, closeList); //Se verifica el nodo izquierdo del nodo superior
                checkF(current, current->getUp()->getRigth(), end, diagonalMovement, openList, closeList); //Se verifica el nodo izquierdo del nodo superior
            }

            if(current->getDown() != nullptr){
                checkF(current, current->getDown()->getLeft(), end, diagonalMovement, openList, closeList); //Se verifica el nodo izquierdo del nodo inferior
                checkF(current, current->getDown()->getRigth(), end, diagonalMovement, openList, closeList); //Se verifica el nodo izquierdo del nodo inferior
            }

        } while (end->getParent() != current && openList->getSize() > 0); //Mientas no se haya llegado al nodo destino y que la openlist este vacia

        LinkedList<PfdMatrixNode<T>*>* path = new LinkedList<PfdMatrixNode<T>*>(); //Camino a seguir para llegar al nodo objetivo
        current = end; //Se reasigna el current como el nodo destino para crear obtener el camino

        while(current != nullptr && end->getParent() != nullptr){ //Se guarda el camino a seguir para llegar al nodo destino
            path->insertAtFirst(current); //Se inserta el nodo actual en la primera posicion de la lista
            current = current->getParent(); //Se obtiene el padre del nodo actual
        }

        return path; //Se retorna el camino desde el nodo inicial para llegar al nodo destino
    }

private:
    /// Metodo para calcular el H de cada nodo de la matriz
    /// \param matrix Matriz en la que calcular el H
    /// \param xEnd Posicion x del nodo objetivo
    /// \param yEnd Posicion y del nodo objetivo
    static void calculateH(PfdMatrix<T>* matrix, int xEnd, int yEnd){
        //Se calcula el H para cada nodo de la lista
        for (int i = 0; i < matrix->getRows(); ++i) { //Se recorren las filas
            for (int j = 0; j < matrix->getColumns(); ++j) { //Se recorren las columnas
                PfdMatrixNode<T> *node1 = matrix->getNode(i, j); //Se obtiene el nodo
                node1->setH(abs(xEnd - i) + abs(yEnd - j)); //Se le calcula el H especifico
            }
        }
    }

    /// Metodo para verificar que el parent de un nodo debe ser actualizado o no
    /// \param current Nodo actual en el recorrido
    /// \param node Nodo al que se le esta verificando el parent
    /// \param end Nodo de llegada
    /// \param movementValue Valor del movimiento a realizar
    /// \param openList LinkedList con los nodos no visitados
    /// \param closeList LinkedList con los nodos visitados
    static void checkF(PfdMatrixNode<T>* current, PfdMatrixNode<T>* node, PfdMatrixNode<T>* end, int movementValue,
                LinkedList<PfdMatrixNode<T> *>* openList, LinkedList<PfdMatrixNode<T> *>* closeList){
        if (node != nullptr) { //Si el nodo es diferente de nulo
            if (node->getData() != 1 && closeList->containsElement(node) == false) { //El nodo no es un obstaculo y no esta dentro de la closelist
                if (node == end) { //Se verifica si es el nodo destino
                    end->setParent(current);
                } else {
                    openList->insertAtEnd(node); //Se inserta el nodo actual en la OpenList
                    int G = current->getG() + movementValue; //Se calcula el nuevo G
                    int F = node->getH() + G; //Se calcula el nuevo F

                    if (F < node->getF()) { //Si el nuevo F es menor al que ya se tenia
                        node->setParent(current); //Se le coloca el current como nuevo parent
                        node->setF(F); //Se le coloca el nuevo F
                        node->setG(G); //Se le coloca el nuevo G
                    }
                }
            }
        }
    }

    /// Metodo que obtiene el elemento con el menor F de la openList
    /// \param openList Lista con los nodos no visitados
    /// \return El nodo con el F menor en la lista
    static PfdMatrixNode<T>* getMinOpenList(LinkedList<PfdMatrixNode<T> *>* openList){
        PfdMatrixNode<T>* minNode = openList->getElement(0)->getData(); //Se obtiene el primer elemento para empezar a comparar
        PfdMatrixNode<T>* current;

        for (int i = 0; i < openList->getSize(); ++i) {
            current = openList->getElement(i)->getData(); //Se obtiene el elemento actual
            if(minNode->getF() > current->getF()) //Se comparan los F del elemento actual y el minimo hasta ahora
                minNode = current; //Se guarda el nuevo minimo
        }

        return minNode; //Se retorna el elemento con el menor F
    }

    static void cleanMatrix(PfdMatrix<T> *matrix){
        for (int i = 0; i < matrix->getRows(); ++i) {
            for (int j = 0; j < matrix->getColumns(); ++j) {
                matrix->getNode(i, j)->setF(std::numeric_limits<int>::max());
                matrix->getNode(i, j)->setG(0);
                matrix->getNode(i, j)->setParent(nullptr);
            }
        }
    }
};


#endif //MILLENNIUMFALCONSIMULATION_A_PATHFINDING_H
