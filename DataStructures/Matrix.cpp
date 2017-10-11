//
// Created by arturocv on 07/10/17.
//

#include "Matrix.h"

template <class T>
Matrix<T>::Matrix(int columns, int rows, T currentNum) {
    Matrix::rows = rows;
    Matrix::columns = columns;

    MatrixNode<T>* previousRow = nullptr; //Referencia a la fila previa a la que se esta creando

    for (int i = 0; i < columns; ++i) { //Se crea el primer nodo de cada columna
        MatrixNode<T>* columnNode = new MatrixNode<T>(currentNum);
        currentNum += 1;
        MatrixNode<T>* current = columnNode;

        //Se asignan las referencias arriba y abajo de los primeros nodos de la fila anterior y la fila actual segun corresponda
        if(previousRow != nullptr){ //Ya la primera fila ha sido creada
            columnNode->setUp(previousRow); //Al nuevo nodo se le asigna el up
            previousRow->setDown(columnNode); //Al primer nodo de la fila anterior se le asigna la referencia down
            previousRow = previousRow->getRigth(); //Se continua con el siguiente nodo de la fila anterior
        }

        if(i == 0) //Es el primer nodo columna que se crea
            Matrix::first = columnNode;

        for (int j = 1; j < rows; ++j) { //Se crean el resto de nodos de cada fila
            MatrixNode<T>* rowNode = new MatrixNode<T>(currentNum); //Se crea el nodo fila
            currentNum += 1;
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

template <class T>
MatrixNode<T>* Matrix<T>::getFirst() {
    return Matrix::first;
}

template <class T>
int Matrix<T>::getColumns() {
    return Matrix::columns;
}

template <class T>
int Matrix<T>::getRows() {
    return Matrix::rows;
}

template <class T>
MatrixNode<T>* Matrix<T>::getNode(int column, int row) {
    if(column < columns && row < rows){ //La posicion ingresada esta dentro de los limites de la matriz
        MatrixNode<T>* node = first;

        for (int i = 0; i < column; ++i) { //Se busca la columna correcta
            node = node->getRigth();
        }

        for (int j = 0; j < row; ++j) { //Se busca en la fila el nodo solicitado
            node = node->getDown();
        }

        return node;

    } else {
        return nullptr; //Datos ingresados sobrepasan los limites de la matriz
    }
}

template <class T>
void Matrix<T>::printMatrix() {
    MatrixNode<T>* currentColumn = first;

    for (int i = 0; i < columns; ++i) {
        std::cout << "[" << currentColumn->getData() << ", ";
        MatrixNode<T>* currentRow = currentColumn->getRigth();

        for (int j = 0; j < rows - 1; ++j) {
            std::cout << currentRow->getData() << ", ";
            currentRow = currentRow->getRigth();
        }

        std::cout << "]" << std::endl;
        currentColumn = currentColumn->getDown();
    }
}
