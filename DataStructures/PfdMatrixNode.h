//
// Created by arturocv on 11/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_PFDMATRIXNODE_H
#define MILLENNIUMFALCONSIMULATION_PFDMATRIXNODE_H


#include <jmorecfg.h>
#include <limits>

template <class T>
class PfdMatrixNode {
private:
    T data;

    int F = std::numeric_limits<int>::max();

    int G = 0;

    int H;

    int rowNum, columnNum;

    PfdMatrixNode<T>* parent = nullptr;

    PfdMatrixNode<T>* right = nullptr;

    PfdMatrixNode<T>* left = nullptr;

    PfdMatrixNode<T>* up = nullptr;

    PfdMatrixNode<T>* down = nullptr;

public:
    PfdMatrixNode(){
    }

    PfdMatrixNode(T data){
        PfdMatrixNode::data = data;
    }

    PfdMatrixNode(int x, int y) {
        PfdMatrixNode::rowNum = x;
        PfdMatrixNode::columnNum = y;
    }

    void setData(T data){
        PfdMatrixNode::data = data;
    }

    T getData(){
        return PfdMatrixNode::data;
    }

    void setF(int F){
        PfdMatrixNode::F = F;
    }

    int getF(){
        return PfdMatrixNode::F;
    }

    void setG(int G){
        PfdMatrixNode::G = G;
    }

    int getG(){
        return PfdMatrixNode::G;
    }

    void setH(int H){
        PfdMatrixNode::H = H;
    }

    int getH(){
        return PfdMatrixNode::H;
    }

    void setParent(PfdMatrixNode<T>* parent){
        PfdMatrixNode::parent = parent;
    }

    PfdMatrixNode<T>* getParent(){
        return PfdMatrixNode::parent;
    }

    PfdMatrixNode<T>* getRigth() {
        return PfdMatrixNode::right;
    }

    void setRight(PfdMatrixNode<T>* node) {
        PfdMatrixNode::right = node;
    }

    PfdMatrixNode<T>* getLeft() {
        return PfdMatrixNode::left;
    }

    void setLeft(PfdMatrixNode<T>* node) {
        PfdMatrixNode::left = node;
    }

    PfdMatrixNode<T>* getUp() {
        return PfdMatrixNode::up;
    }

    void setUp(PfdMatrixNode<T>* node) {
        PfdMatrixNode::up = node;
    }

    PfdMatrixNode<T>* getDown() {
        return PfdMatrixNode::down;
    }

    void setDown(PfdMatrixNode<T>* node) {
        PfdMatrixNode::down = node;
    }

    int getRowNum(){
        return  PfdMatrixNode::rowNum;
    }

    int getColumnNum(){
        return  PfdMatrixNode::columnNum;
    }

    bool operator==(PfdMatrixNode<T> &node) {
        if(this == &node) return (true);
        return (false);
    }
};


#endif //MILLENNIUMFALCONSIMULATION_PFDMATRIXNODE_H
