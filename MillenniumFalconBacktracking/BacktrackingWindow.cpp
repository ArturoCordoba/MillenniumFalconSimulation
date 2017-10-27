//
// Created by arturocv on 26/10/17.
//

#include "BacktrackingWindow.h"

int BacktrackingWindow::xSize = 1200; //Cantidad de pixeles horizontales de la pantalla
int BacktrackingWindow::ySize = 720; //Cantidad de pixeles verticales de la pantalla

int BacktrackingWindow::getXSize() {
    return BacktrackingWindow::xSize;
}

int BacktrackingWindow::getYSize() {
    return BacktrackingWindow::ySize;
}

///Metodo para renderizar la ventana
void BacktrackingWindow::render() {
    sf::Texture bgTexture; //Textura del fondo
    sf::Sprite backgroundSprite; //Sprite del fondo
    bgTexture.loadFromFile("resources/background.jpg"); //Se carga la textura del fond
    backgroundSprite.setTexture(bgTexture); //Se le coloca la textura al sprite del fondo
    backgroundSprite.setScale(1.0f, 1.0f); //Se le coloca la escala al sprite del fondo
    backgroundSprite.setTexture(bgTexture); //Se le coloca la textura al sprite del fondo
    backgroundSprite.setScale(1.0f, 1.0f); //Se le coloca la escala al sprite del fondo

    sf::Texture rebelBaseTexture; //Textura de la base rebelde
    sf::Sprite rebelBase; //Sprite de la base rebelde
    rebelBaseTexture.loadFromFile("resources/rebelbase.png"); //Se carga la textura
    rebelBase.setTexture(rebelBaseTexture); //Se le coloca la textura al sprite
    rebelBase.setScale(0.35f, 0.35f); //Se le coloca la escala
    rebelBase.setPosition(1020, 550); //Se le coloca la posicion

    sf::Clock clock; //Controlador del tiempo
    float frameCounter = 0, switchFrame = 20, frameSpeed = 500, elapsedTime;
    int xTexture = 0; //Posicion en x de las texturas de los asteroides
    sf::Texture asteriodTexture;
    asteriodTexture.loadFromFile("resources/asteroid.png"); //Se carga la textura de los asteroides
    int xMaxTexture = asteriodTexture.getSize().x;

    sf::Vector2i screenDimensions(xSize, ySize); //Vector que almacena las dimensiones de la pantalla
    sf::RenderWindow window;
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Millennium Falcon A*"); //Se crea la ventana

    asteroidList = LinkedList<Asteroid*>(); //Lista con todos los asteroides

    millenniumFalcon = new MillenniumFalcon(); //Se crea la nave principal

    createMatrix(85); //Se crean los asteroides

    LinkedList<BtkMatrixNode<int>*>* path = Backtracking::searchSolution(matrix->getFirst());

    if(path->getSize() > 0){
        current = path->getElement(0); //Se obtiene el nodo inicial del recorrido
    }

    while (window.isOpen()) { //Mientras la ventana este abierta
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) //Se presiono el boton de cerrar la ventana
                window.close();

        }

        window.clear(); //Se limpia la ventana
        window.draw(backgroundSprite); //Se dibuja el fondo
        window.draw(rebelBase);
        window.draw(*millenniumFalcon->getSprite()); //Se dibuja el Millennium Falcon

        elapsedTime = clock.restart().asSeconds();
        frameCounter += frameSpeed * elapsedTime;

        if(frameCounter >= switchFrame) {
            frameCounter = 0; //Se reinicia el contador
            xTexture += 60; //Se suman 60 pixeles a la posicion en x de la textura de los asteroides
            if (xTexture >= xMaxTexture) //Se ha llegado al final de la textura de los asteroides
                xTexture = 0;  //Se reinicia en cero

            //Se realiza la animacion de los asteroides
            for (int i = 0; i < asteroidList.getSize(); ++i) {
                Asteroid* asteroid = asteroidList.getElement(i)->getData(); //Se obtiene el asteroide
                asteroid->getSprite()->setTextureRect(sf::IntRect(xTexture, 0, 60, 60)); //Se cambia la textura del sprite
            }

            if(path->getSize() > 0) { //Si el camino existe
                moveShip(); //Se mueve la nave
            }
        }

        //Se dibujan los asteroides
        for (int j = 0; j < asteroidList.getSize(); ++j) {
            window.draw(*asteroidList.getElement(j)->getData()->getSprite());
        }

        window.display(); //Se renderiza t0do en la pantalla
    }
}

/// Metodo que crea la matriz junto con los asteroides
/// \param maxAsteroids Numero maximo de asteroides deseados
void BacktrackingWindow::createMatrix(int maxAsteroids) {
    srand(time(NULL));

    int rows = ySize / 60; //Se obtiene el numero de filas
    int columns = xSize / 60; //Se obtiene el numero de columnas

    matrix = new BtkMatrix<int>(rows, columns); //Se crea la matriz

    //Se colocan ceros en cada posicion de la matriz
    for (int i = 0; i < matrix->getRows(); ++i) { //Se recorren las filas
        for (int j = 0; j < matrix->getColumns(); ++j) { //Se recorren las columnas
            BtkMatrixNode<int>* node = matrix->getNode(i, j); //Se obtiene el nodo en la posicion especifica
            node->setData(0); //Se coloca en cero en el nodo
        }
    }

    matrix->setElement(rows -1, columns - 1, 2); //Se establece la meta

    for (int i = 0; i < maxAsteroids; ++i) { //Se crean como una cantidad maxAsteroids de asteroides
        int x = 0 + rand() % (rows); //Se obtiene una posicion random en x
        int y = 0 + rand() % (columns); //Se obtiene una posicion random en y

        if(x != 0 || y != 0){ //Si la posicion no corresponde a la casilla inicial
            if(y != (columns) - 1 || x != (rows) - 1){ //Si la posicion no corresponde a la casilla final
                asteroidList.insertAtFirst(new Asteroid(y * 60, x * 60, 0, 0)); //Se inserta un nuevo asteroide en la casilla de asteroides
                matrix->getNode(x, y)->setData(1); //Se coloca un uno en la posicion en la matriz
            }
        }
    }
}

///Metodo para mover la nave espacial
void BacktrackingWindow::moveShip() {
    int x = millenniumFalcon->getSprite()->getPosition().x; //Posicion en x actual
    int y = millenniumFalcon->getSprite()->getPosition().y; //Posicion en y actual

    if(current->getData()->getData() != 2){ //Mientras no se haya alcanzado el destino
        int xNext = current->getNext()->getData()->getColumnNum() * 60; //Se obtiene la posicion en x del nodo siguiente
        int yNext = current->getNext()->getData()->getRowNum() * 60; //Se obitene la posicion en y del nodo siguiente

        if((x == xNext) && (y == yNext)){ //Se ha alcanzado la posicion del nodo siguiente
            current = current->getNext(); //Se avanza al siguiente nodo
        }

        if(current->getNext() != nullptr) { //Mientras no se haya alcanzado el destino
            BtkMatrixNode<int> *actualNode = current->getData(); //Se obtiene el MatrixNode actual
            BtkMatrixNode<int> *nextNode = current->getNext()->getData(); //Se obtiene el MatrixNode siguiente

            if (nextNode->getRowNum() - actualNode->getRowNum() < 0) { //El movimiento es hacia arriba
                millenniumFalcon->setXMov(0);
                millenniumFalcon->setYMov(-5);
            } else if (nextNode->getRowNum() - actualNode->getRowNum() > 0) { //El movimiento es hacia abajo
                millenniumFalcon->setXMov(0);
                millenniumFalcon->setYMov(5);
            } else if (nextNode->getColumnNum() - actualNode->getColumnNum() < 0) { //El movimiento es a la izquierda
                millenniumFalcon->setYMov(0);
                millenniumFalcon->setXMov(-5);
            } else if (nextNode->getColumnNum() - actualNode->getColumnNum() > 0) { //El movimiento es a la derecha
                millenniumFalcon->setYMov(0);
                millenniumFalcon->setXMov(5);
            }
        }
    } else{
        millenniumFalcon->setXMov(0); //Se detiene el movimiento en x
        millenniumFalcon->setYMov(0); //Se detiene el movimiento en y
    }
    millenniumFalcon->move(); //Se realiza el movimientp
}
