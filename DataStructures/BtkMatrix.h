//
// Created by arturocv on 07/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_MATRIX_H
#define MILLENNIUMFALCONSIMULATION_MATRIX_H

#include <iostream>
#include "BtkMatrixNode.h"

template <class T>
class BtkMatrix {
public:
    /// Constructor de la clase
    /// \param rows Numero de filas de la matriz
    /// \param columns Numero de columnas de la matriz
    BtkMatrix(int rows, int columns) {
        BtkMatrix::rows = rows;
        BtkMatrix::columns = columns;

        BtkMatrixNode<T>* previousRow = nullptr; //Referencia a la fila previa a la que se esta creando

        for (int i = 0; i < rows; ++i) { //Se crea el primer nodo de cada columna
            BtkMatrixNode<T>* columnNode = new BtkMatrixNode<T>();
            BtkMatrixNode<T>* current = columnNode;

            //Se asignan las referencias arriba y abajo de los primeros nodos de la fila anterior y la fila actual segun corresponda
            if(previousRow != nullptr){ //Ya la primera fila ha sido creada
                columnNode->setUp(previousRow); //Al nuevo nodo se le asigna el up
                previousRow->setDown(columnNode); //Al primer nodo de la fila anterior se le asigna la referencia down
                previousRow = previousRow->getRigth(); //Se continua con el siguiente nodo de la fila anterior
            }

            if(i == 0) //Es el primer nodo columna que se crea
                BtkMatrix::first = columnNode;

            for (int j = 1; j < columns; ++j) { //Se crean el resto de nodos de cada fila
                BtkMatrixNode<T>* rowNode = new BtkMatrixNode<T>(); //Se crea el nodo fila
                rowNode->setLeft(current); //Al nuevo nodo fila se le asigna el nodo que tiene a la izquierda
                current->setRight(rowNode); //El nodo que esta a la izquierda del nuevo nodo, se le asigna el nuevo nodo como right

                if(previousRow != nullptr){
                    rowNode->setUp(previousRow); //Se le asigna al nuevo nodo el nodo superior
                    previousRow->setDown(rowNode); //Al nodo superior del nuevo nodo se le asigna la referencia hacia abajo
                    previousRow = previousRow->getRigth(); //El previousRow avanza hacia la derecha
                }

                current = rowNode; //El current se convierte en el nuevo nodo

            }

            previousRow = columnNode; //Se reasigna la fila previa
        }
    }

    BtkMatrixNode<T>* getFirst() {
        return BtkMatrix::first;
    }

    int getColumns() {
        return BtkMatrix::columns;
    }

    int getRows() {
        return BtkMatrix::rows;
    }

    /// Metodo para obtener un nodo de la matriz
    /// \param row Numero de fila en la que esta el nodo
    /// \param column Numero de columna en la que esta el nodo
    /// \return El nodo solicitado, nullptr si la posicion ingresada esta fuera de los limites
    BtkMatrixNode<T>* getNode(int row, int column) {
        if(row < rows && column < columns){ //La posicion ingresada esta dentro de los limites de la matriz
            BtkMatrixNode<T>* node = first;

            for (int i = 0; i < row; ++i) { //Se busca la columna correcta
                node = node->getDown();
            }

            for (int j = 0; j < column; ++j) { //Se busca en la fila el nodo solicitado
                node = node->getRigth();
            }

            return node;

        } else {
            return nullptr; //Datos ingresados sobrepasan los limites de la matriz
        }
    };

    /// Metodo para establecer un elemento en uno de los nodos de la matriz
    /// \param column Numero de columna en la matriz
    /// \param row Numero de fila en la matriz
    /// \param data Elemento a establecer
    void setElement(int row, int column, T data) {
        if(column < columns && row < rows){ //La posicion ingresada esta dentro de los limites de la matriz
            BtkMatrixNode<T>* node = first;

            for (int i = 0; i < row; ++i) { //Se busca la columna correcta
                node = node->getDown();
            }

            for (int j = 0; j < column; ++j) { //Se busca en la fila el nodo solicitado
                node = node->getRigth();
            }

            node->setData(data);
        }
    }

    ///Metodo para imprimir la matriz por consola
    void printMatrix() {
        BtkMatrixNode<T>* currentColumn = first;

        for (int i = 0; i < rows; ++i) {
            std::cout << "[" << currentColumn->getData() << ", ";
            BtkMatrixNode<T>* currentRow = currentColumn->getRigth();

            for (int j = 0; j < columns - 1; ++j) {
                std::cout << currentRow->getData() << ", ";
                currentRow = currentRow->getRigth();
            }

            std::cout << "]" << std::endl;
            currentColumn = currentColumn->getDown();
        }
    }

private:
    BtkMatrixNode<T>* first; //Punto de entrada a la matriz, nodo de la esquina superior izquierda

    int rows; //Numero de filas de la matriz

    int columns; //Numero de columnas

};


#endif //MILLENNIUMFALCONSIMULATION_MATRIX_H
