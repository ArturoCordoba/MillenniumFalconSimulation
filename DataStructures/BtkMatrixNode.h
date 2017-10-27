//
// Created by arturocv on 07/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_MATRIXNODE_H
#define MILLENNIUMFALCONSIMULATION_MATRIXNODE_H

template <class T>
class BtkMatrixNode {
public:
    BtkMatrixNode(){

    }

    BtkMatrixNode(T data) {
        BtkMatrixNode::data = data;
    }

    BtkMatrixNode(int x, int y) {
        BtkMatrixNode::rowNum = x;
        BtkMatrixNode::columnNum = y;
    }

    T getData() {
        return BtkMatrixNode::data;
    }

    void setData(T data) {
        BtkMatrixNode::data = data;
    }

    BtkMatrixNode<T>* getRigth() {
        return BtkMatrixNode::right;
    }

    void setRight(BtkMatrixNode<T>* node) {
        BtkMatrixNode::right = node;
    }

    BtkMatrixNode<T>* getLeft() {
        return BtkMatrixNode::left;
    }

    void setLeft(BtkMatrixNode<T>* node) {
        BtkMatrixNode::left = node;
    }

    BtkMatrixNode<T>* getUp() {
        return BtkMatrixNode::up;
    }

    void setUp(BtkMatrixNode<T>* node) {
        BtkMatrixNode::up = node;
    }

    BtkMatrixNode<T>* getDown() {
        return BtkMatrixNode::down;
    }

    void setDown(BtkMatrixNode<T>* node) {
        BtkMatrixNode::down = node;
    }

    int getRowNum(){
        return  BtkMatrixNode::rowNum;
    }

    int getColumnNum(){
        return  BtkMatrixNode::columnNum;
    }

    bool operator==(BtkMatrixNode<T> &node) {
        if(this == &node) return (true);
        return (false);
    }

private:
    T data;

    BtkMatrixNode<T>* right = nullptr;

    BtkMatrixNode<T>* left = nullptr;

    BtkMatrixNode<T>* up = nullptr;

    BtkMatrixNode<T>* down = nullptr;

    int rowNum;

    int columnNum;
};


#endif //MILLENNIUMFALCONSIMULATION_MATRIXNODE_H

