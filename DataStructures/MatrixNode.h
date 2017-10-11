//
// Created by arturocv on 07/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_MATRIXNODE_H
#define MILLENNIUMFALCONSIMULATION_MATRIXNODE_H

template <class T>
class MatrixNode {
public:
    MatrixNode();

    MatrixNode(T data);

    MatrixNode(T data, MatrixNode<T>* left, MatrixNode* up);

    T getData();

    void setData(T data);

    MatrixNode<T>* getRigth();

    void setRight(MatrixNode<T>* node);

    MatrixNode<T>* getLeft();

    void setLeft(MatrixNode<T>* node);

    MatrixNode<T>* getUp();

    void setUp(MatrixNode<T>* node);

    MatrixNode<T>* getDown();

    void setDown(MatrixNode<T>* node);

    bool operator==(MatrixNode<T> &node);

private:
    T data;
    MatrixNode<T>* right = nullptr;
    MatrixNode<T>* left = nullptr;
    MatrixNode<T>* up = nullptr;
    MatrixNode<T>* down = nullptr;
};


#endif //MILLENNIUMFALCONSIMULATION_MATRIXNODE_H
