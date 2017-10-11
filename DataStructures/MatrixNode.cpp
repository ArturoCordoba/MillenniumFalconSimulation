//
// Created by arturocv on 07/10/17.
//

#include "MatrixNode.h"


template <class T>
MatrixNode<T>::MatrixNode() {
}

template <class T>
MatrixNode<T>::MatrixNode(T data) {
    MatrixNode::data = data;
}

template <class T>
MatrixNode<T>::MatrixNode(T data, MatrixNode<T> *left, MatrixNode *up) {
    MatrixNode::data = data;
    MatrixNode::left = left;
    MatrixNode::up = up;
}

template <class T>
T MatrixNode<T>::getData() {
    return MatrixNode::data;
}

template <class T>
void MatrixNode<T>::setData(T data) {
    MatrixNode::data = data;
}

template <class T>
MatrixNode<T>* MatrixNode<T>::getRigth() {
    return MatrixNode::right;
}

template <class T>
void MatrixNode<T>::setRight(MatrixNode<T> *node) {
    MatrixNode::right = node;
}

template <class T>
MatrixNode<T>* MatrixNode<T>::getLeft() {
    return MatrixNode::left;
}

template <class T>
void MatrixNode<T>::setLeft(MatrixNode<T> *node) {
    MatrixNode::left = node;
}

template <class T>
MatrixNode<T>* MatrixNode<T>::getUp() {
    return MatrixNode::up;
}

template <class T>
void MatrixNode<T>::setUp(MatrixNode<T> *node) {
    MatrixNode::up = node;
}

template <class T>
MatrixNode<T>* MatrixNode<T>::getDown() {
    return MatrixNode::down;
}

template <class T>
void MatrixNode<T>::setDown(MatrixNode<T> *node) {
    MatrixNode::down = node;
}

template <class T>
bool MatrixNode<T>::operator==(MatrixNode<T> &node) {
    if(this == &node) return (true);
    return (false);
}