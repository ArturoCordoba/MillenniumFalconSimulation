//
// Created by arturocv on 07/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_MATRIX_H
#define MILLENNIUMFALCONSIMULATION_MATRIX_H

#include <iostream>
#include "MatrixNode.cpp"

template <class T>
class Matrix {
public:
    Matrix(int columns, int rows, T currentNum);

    void printMatrix();

    MatrixNode<T>* getFirst();

    int getColumns();

    int getRows();

    MatrixNode<T>* getNode(int column, int row);

private:
    MatrixNode<T>* first; //Punto de entrada a la matriz, nodo de la esquina superior izquierda

    int rows; //Numero de filas de la matriz

    int columns; //Numero de columnas

};


#endif //MILLENNIUMFALCONSIMULATION_MATRIX_H
