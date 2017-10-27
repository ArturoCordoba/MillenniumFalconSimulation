#include <SFML/Graphics.hpp>

#include "MillenniumFalconBacktracking/BacktrackingWindow.h"

using namespace std;

int main()
{
    BacktrackingWindow gameWindow = BacktrackingWindow();
    gameWindow.render();



    /*Test test = Test();
    test.render();*/

    /*BtkMatrix<int>* matrix = new BtkMatrix<int>(12, 20);

    for (int i = 0; i < matrix->getRows(); ++i) {
        for (int j = 0; j < matrix->getColumns(); ++j) {

            BtkMatrixNode<int>* node = matrix->getNode(i, j);
            node->setData(0);
        }
    }

    matrix->setElement(0, 5, 1);
    matrix->setElement(0, 7, 1);
    matrix->setElement(0, 8, 1);
    matrix->setElement(0, 9, 1);
    matrix->setElement(0, 16, 1);
    matrix->setElement(0, 17, 1);
    matrix->setElement(0, 18, 1);

    matrix->setElement(1, 5, 1);
    matrix->setElement(1, 8, 1);
    matrix->setElement(1, 10, 1);
    matrix->setElement(1, 11, 1);
    matrix->setElement(1, 15, 1);
    matrix->setElement(1, 19, 1);

    matrix->setElement(2, 3, 1);
    matrix->setElement(2, 4, 1);
    matrix->setElement(2, 5, 1);
    matrix->setElement(2, 16, 1);
    matrix->setElement(2, 18, 1);
    matrix->setElement(2, 19, 1);

    matrix->setElement(3, 8, 1);
    matrix->setElement(3, 13, 1);
    matrix->setElement(3, 18, 1);
    matrix->setElement(3, 19, 1);

    matrix->setElement(4, 1, 1);
    matrix->setElement(4, 7, 1);
    matrix->setElement(4, 9, 1);
    matrix->setElement(4, 14, 1);
    matrix->setElement(4, 17, 1);
    matrix->setElement(4, 18, 1);

    matrix->setElement(5, 9, 1);
    matrix->setElement(5, 11, 1);
    matrix->setElement(5, 12, 1);
    matrix->setElement(5, 13, 1);
    matrix->setElement(5, 14, 1);
    matrix->setElement(5, 16, 1);
    matrix->setElement(5, 19, 1);

    matrix->setElement(6, 7, 1);
    matrix->setElement(6, 9, 1);
    matrix->setElement(6, 11, 1);
    matrix->setElement(6, 13, 1);

    matrix->setElement(7, 1, 1);
    matrix->setElement(7, 9, 1);
    matrix->setElement(7, 10, 1);
    matrix->setElement(7, 12, 1);
    matrix->setElement(7, 13, 1);
    matrix->setElement(7, 14, 1);
    matrix->setElement(7, 15, 1);
    matrix->setElement(7, 17, 1);
    matrix->setElement(7, 18, 1);

    matrix->setElement(8, 0, 1);
    matrix->setElement(8, 2, 1);
    matrix->setElement(8, 3, 1);
    matrix->setElement(8, 4, 1);
    matrix->setElement(8, 7, 1);
    matrix->setElement(8, 8, 1);
    //matrix->setElement(8, 16, 1);

    matrix->setElement(9, 0, 1);
    matrix->setElement(9, 1, 1);
    matrix->setElement(9, 2, 1);
    matrix->setElement(9, 3, 1);
    matrix->setElement(9, 4, 1);
    matrix->setElement(9, 5, 1);
    matrix->setElement(9, 6, 1);
    matrix->setElement(9, 7, 1);
    matrix->setElement(9, 8, 1);
    matrix->setElement(9, 9, 1);
    matrix->setElement(9, 10, 1);
    matrix->setElement(9, 11, 1);
    matrix->setElement(9, 12, 1);
    matrix->setElement(9, 13, 1);
    matrix->setElement(9, 14, 1);
    matrix->setElement(9, 15, 1);

    matrix->setElement(9, 0, 1);
    matrix->setElement(9, 2, 1);
    matrix->setElement(9, 3, 1);
    matrix->setElement(9, 6, 1);
    matrix->setElement(9, 10, 1);
    matrix->setElement(9, 11, 1);
    matrix->setElement(9, 12, 1);
    matrix->setElement(9, 13, 1);
    matrix->setElement(9, 14, 1);
    matrix->setElement(9, 15, 1);
    matrix->setElement(9, 17, 1);
    matrix->setElement(9, 18, 1);
    matrix->setElement(9, 19, 1);

    matrix->setElement(10, 0, 1);
    matrix->setElement(10, 2, 1);
    matrix->setElement(10, 3, 1);
    matrix->setElement(10, 6, 1);
    matrix->setElement(10, 7, 1);
    matrix->setElement(10, 11, 1);
    matrix->setElement(10, 13, 1);
    matrix->setElement(10, 14, 1);
    matrix->setElement(10, 17, 1);

    matrix->setElement(11, 1, 1);
    matrix->setElement(11, 3, 1);
    matrix->setElement(11, 6, 1);
    matrix->setElement(11, 9, 1);
    matrix->setElement(11, 11, 1);
    matrix->setElement(11, 13, 1);

    //matrix->setElement(11, 19, 2);

    matrix->printMatrix();

    cout << endl;

    LinkedList<BtkMatrixNode<int>*>* list = Backtracking::searchSolution(matrix->getFirst());

    for (int i = 0; i < list->getSize(); ++i) {
        list->getElement(i)->getData()->setData(5);
    }

    matrix->printMatrix();*/



    /*PfdMatrix<int>* matrix = new PfdMatrix<int>(12, 20);

    for (int i = 0; i < matrix->getRows(); ++i) {
        for (int j = 0; j < matrix->getColumns(); ++j) {
            matrix->setElement(i, j, 0);
        }
    }

    matrix->setElement(0, 0, 2);
    matrix->setElement(13, 23, 2);

    /*matrix->setElement(0, 2, 1);
    matrix->setElement(1, 2, 1);

    matrix->setElement(1, 4, 1);
    matrix->setElement(1, 5, 1);

    matrix->setElement(3, 1, 1);
    matrix->setElement(3, 2, 1);
    matrix->setElement(3, 3, 1);

    matrix->setElement(5, 2, 1);
    matrix->setElement(6, 2, 1);

    matrix->setElement(5, 4, 1);
    matrix->setElement(5, 5, 1);


    matrix->printMatrix();

    cout << endl;

    LinkedList<PfdMatrixNode<int>*>* path = Pathfinding_A<int>::calculatePath(matrix, 0, 0, 11, 19, 10, 14);

    for (int k = 0; k < path->getSize(); ++k) {
        path->getElement(k)->getData()->setData(5);
    }

    matrix->printMatrix();*/







    /*BtkMatrix<int>* matrix = new BtkMatrix<int>(7, 7);

    for (int i = 0; i < matrix->getRows(); ++i) {
        for (int j = 0; j < matrix->getColumns(); ++j) {

            BtkMatrixNode<int>* node = matrix->getNode(i, j);
            node->setData(0);
        }
    }


    /*matrix->setElement(0, 4, 1);
    matrix->setElement(1, 1, 1);
    matrix->setElement(1, 2, 1);
    matrix->setElement(1, 3, 1);
    matrix->setElement(1, 4, 1);
    matrix->setElement(2, 1, 1);
    matrix->setElement(2, 3, 1);
    matrix->setElement(3, 3, 1);
    matrix->setElement(3, 5, 1);
    matrix->setElement(4, 1, 1);
    matrix->setElement(4, 2, 1);
    matrix->setElement(4, 3, 1);
    matrix->setElement(4, 5, 1);
    matrix->setElement(5, 1, 1);
    matrix->setElement(5, 5, 1);
    matrix->setElement(6, 3, 1);
    matrix->setElement(6, 5, 1);
    matrix->setElement(6, 6, 2);



    matrix->printMatrix();

    cout << endl;

    LinkedList<BtkMatrixNode<int>*>* list = Backtracking::searchSolution(matrix->getFirst());

    for (int i = 0; i < list->getSize(); ++i) {
        list->getElement(i)->getData()->setData(5);
    }

    matrix->printMatrix();*/


    /*int xPos = 60;
    int correction = xPos % 60;
    int result;

    if(correction > 30){
        result = xPos + (60 - correction);
        cout << "Correccion: " << 60 - correction << " / Result: " << (result) << endl;
    } else{
        result = xPos - correction;
        cout << "Correccion: " << correction << " / Result: " << (result) << endl;
    }*/

    /*int yPos = 92;
    int correctionY = yPos % 60; //Se calcula la correccion
    int resultY = yPos;

    if(correctionY > 30){
        resultY = yPos + (60 - correctionY);
        cout << "Correccion: " << 60 - correctionY << " / Result: " << (resultY) << endl;
    } else {
        resultY = yPos - correctionY;
        cout << "Correccion: " << correctionY << " / Result: " << (resultY) << endl;
    }*/


}