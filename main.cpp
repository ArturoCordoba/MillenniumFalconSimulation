#include <SFML/Graphics.hpp>

#include "MillenniumFalconBacktracking/BacktrackingWindow.h"
#include "MillenniumFalconA*/PathfindingWindow.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int option;
    bool done = false;

    BacktrackingWindow gameWindow = BacktrackingWindow();
    PathfindingWindow gameWindow2 = PathfindingWindow();

    while(!done)
    {
        cout << "Simulacion de Millenium Falcon\n" << endl;
        cout << "1 - Pathfinding A*" << endl;
        cout << "2 - Backtracking" << endl;
        cout << "3 - Salir" << endl;
        cout << "Seleccione una simulacion: " << endl;
        cin >> option;

        switch (option)
        {
            case 1:
                gameWindow2.render();
                break;
            case 2:
                gameWindow.render();
                break;
            case 3:
                cout << "Adios!" << endl;
                done = true;
                break;
            default:
                cout << "Intente de nuevo!" << endl;
        }
        cout << endl;
    }
    return 0;
}
