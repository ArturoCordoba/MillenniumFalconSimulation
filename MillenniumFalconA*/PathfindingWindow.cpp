//
// Created by arturocv on 16/10/17.
//

#include "PathfindingWindow.h"
#include "Explosion.h"
#include "../DataStructures/PfdMatrix.h"
#include "PathfindingA.h"

int PathfindingWindow::xSize = 1200;
int PathfindingWindow::ySize = 720;
int PathfindingWindow::maxAsteroids = 30;

int PathfindingWindow::getXSize() {
    return PathfindingWindow::xSize;
}

int PathfindingWindow::getYSize() {
    return PathfindingWindow::ySize;
}

int PathfindingWindow::getMaxAsteroids() {
    return PathfindingWindow::maxAsteroids;
}

void PathfindingWindow::render() {
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
    tieFightersList = LinkedList<TIE_Fighter*>(); //Lista con todos los TIE Fighters
    explosionList = LinkedList<Explosion*>();

    millenniumFalcon = new MillenniumFalcon(); //Se crea la nave principal

    createMap1();

    LinkedList<PfdMatrixNode<int>*>* path = PathfindingA<int>::calculatePath(matrix, matrix->getFirst()->getRowNum(), matrix->getFirst()->getColumnNum(),
                                                                             matrix->getRows() -1, matrix->getColumns() -1, 10, 100000); //Se calcula el camino

    current = path->getElement(0);

    //tieFightersList.insertAtFirst(createTIEFighter(0, 420, 1.5, 0));

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
            frameCounter = 0;
            xTexture += 60;
            if (xTexture >= xMaxTexture)
                xTexture = 0;

            for (int i = 0; i < asteroidList.getSize(); ++i) {
                Asteroid* asteroid = asteroidList.getElement(i)->getData(); //Se obtiene el asteroide
                asteroid->getSprite()->setTextureRect(sf::IntRect(xTexture, 0, 60, 60)); //Se cambia la textura del sprite
                asteroid->move();
            }

            for (int j = 0; j < tieFightersList.getSize(); ++j) {
                TIE_Fighter* fighter = tieFightersList.getElement(j)->getData();
                fighter->move();
            }

            for (int k = 0; k < explosionList.getSize(); ++k) {
                Explosion* explosion = explosionList.getElement(k)->getData();
                explosion->currentX += 64;
                explosion->getSprite()->setTextureRect(sf::IntRect(explosion->currentX, 0, 64, 64));
            }

            checkCollisions();
            updateMap(); //Se actualiza la matriz
            moveMillenniumFalcon();
        }

        for (int l = 0; l < asteroidList.getSize(); ++l) {
            window.draw(*asteroidList.getElement(l)->getData()->getSprite());
        }

        for (int m = 0; m < tieFightersList.getSize(); ++m) {
            window.draw(*tieFightersList.getElement(m)->getData()->getSprite());
        }

        for (int n = 0; n < explosionList.getSize(); ++n) {
            window.draw(*explosionList.getElement(n)->getData()->getSprite());
        }


        window.display();
    }
}

/// Metodo para crear un nuevo asteroide
/// \param x Posicion en x
/// \param y Posicion en y
/// \param xMov Movimiento en x
/// \param yMov Movimiento en y
/// \return Asteroide
Asteroid* PathfindingWindow::createAsteroid(int x, int y, float xMov, float yMov) {
    Asteroid* asteroid = new Asteroid(x, y, xMov, yMov);
    return asteroid;
}

/// Metodo para crear un nuevo TIE Fighter
/// \param x Posicion en x
/// \param y Posicion en y
/// \param xMov Movimiento en x
/// \param yMov Movimiento en y
/// \return Nuevo TIE Fighter
TIE_Fighter* PathfindingWindow::createTIEFighter(int x, int y, float xMov, float yMov) {
    TIE_Fighter* fighter = new TIE_Fighter(x, y, xMov, yMov);
    return fighter;
}

void PathfindingWindow::checkCollisions() {
    millenniumFalcon->update();

    for (int i = 0; i < asteroidList.getSize(); ++i) {
        Asteroid* asteroid = asteroidList.getElement(i)->getData(); //Se obtiene el asteroide
        asteroid->update();
    }

    LinkedList<sf::Vector2f> collisionList = LinkedList<sf::Vector2f>(); //Lista que guarda las colisiones

    for (int j = 0; j < asteroidList.getSize(); ++j) {
        Asteroid* asteroid1 = asteroidList.getElement(j)->getData(); //Se obtiene el asteroide 1

        for (int k = 0; k < asteroidList.getSize(); ++k) {
            if(j != k){ //Se verifica que no correspondan al mismo asteroide
                Asteroid* asteroid2 = asteroidList.getElement(k)->getData(); //Se obtiene el asteroide 2

                if(asteroid1->checkCollision(asteroid2)) { //Existe una colision entre los asteroides
                    bool checked = false; //Bool que establece si esta colision ya ha sido revisada

                    for (int l = 0; l < collisionList.getSize(); ++l) { //Se recorre la lista de colisiones para verificar
                        if(j == collisionList.getElement(l)->getData().y && k == collisionList.getElement(l)->getData().x){
                            checked = true; //La colision ha sido revisada anteriormente
                        }
                    }

                    if(checked == false){ //La colision no ha sido revisada
                        asteroidCollision(asteroid1, asteroid2);
                        collisionList.insertAtFirst(sf::Vector2f(j, k)); //Se guarda la colision en la lista
                        asteroid1->substractLive();
                        asteroid2->substractLive();
                    }
                }
            }
        }
    }

    for (int m = 0; m < asteroidList.getSize(); ++m) {
        Asteroid* asteroid = asteroidList.getElement(m)->getData();
        if (asteroid->getLives() < 0){
            explosionList.insertAtFirst(new Explosion(asteroid->getSprite()->getPosition().x, asteroid->getSprite()->getPosition().y));
            Node<Asteroid*>* node = asteroidList.getElement(m);
            asteroidList.deleteElement(m);
            free(asteroid);
            free(node);
        }
    }
}

/// Metodo para dividir los asteroides cuando colisiones
/// \param asteroid1 Asteroide uno
/// \param asteroid2 Asteroide dos
void PathfindingWindow::asteroidCollision(Asteroid *asteroid1, Asteroid *asteroid2) {
    asteroid1->correctPosition();
    asteroid2->correctPosition();

    if(asteroid1->getXMov() != 0)
        asteroid1->changeXDirection();

    if(asteroid1->getYMov() != 0)
        asteroid1->changeYDirection();

    if(asteroid2->getXMov() != 0)
        asteroid2->changeXDirection();

    if(asteroid2->getYMov() != 0)
        asteroid2->changeYDirection();

    Asteroid* newAsteroid1 = nullptr;
    Asteroid* newAsteroid2 = nullptr;

    if(asteroid1->getXMov() != 0 & asteroid2->getXMov() != 0){
        float x = asteroid1->getSprite()->getPosition().x;
        float y1 = asteroid1->getSprite()->getPosition().y + asteroid1->getSprite()->getTextureRect().height;
        float y2 = asteroid1->getSprite()->getPosition().y - asteroid1->getSprite()->getTextureRect().height;

        if(x > 0 && x < PathfindingWindow::xSize && y1 > 0 && y1 < PathfindingWindow::ySize) //Se verifica que la posicion este dentro de los limites de la pantalla
            newAsteroid1 = createAsteroid(x, y1, 0, 1);

        if(x > 0 && x < PathfindingWindow::xSize && y2 > 0 && y2 < PathfindingWindow::ySize)
           newAsteroid2 = createAsteroid(x, y2, 0, -1);


    } else if(asteroid1->getYMov() != 0 && asteroid2->getYMov() != 0){
        float x1 = asteroid1->getSprite()->getPosition().x + asteroid1->getSprite()->getTextureRect().width;
        float x2 = asteroid1->getSprite()->getPosition().x - asteroid1->getSprite()->getTextureRect().width;
        float y = asteroid1->getSprite()->getPosition().y;

        if(x1 > 0 && x1 < PathfindingWindow::xSize && y > 0 && y < PathfindingWindow::ySize)
            newAsteroid1 = createAsteroid(x1, y, 1, 0);

        if(x2 > 0 && x2 < PathfindingWindow::xSize && y > 0 && y < PathfindingWindow::ySize)
            newAsteroid2 = createAsteroid(x2, y, -1, 0);

    } else if(asteroid1->getXMov() != 0 && asteroid2->getYMov() != 0){
        float x1 = asteroid1->getSprite()->getPosition().x;
        float y1 = asteroid1->getSprite()->getPosition().y + asteroid1->getSprite()->getTextureRect().height;
        float x2 = asteroid2->getSprite()->getPosition().x - asteroid2->getSprite()->getTextureRect().width;
        float y2 = asteroid2->getSprite()->getPosition().y;

        if(x1 > 0 && x1 < PathfindingWindow::xSize && y1 > 0 && y1 < PathfindingWindow::ySize)
            newAsteroid1 = createAsteroid(x1, y1, asteroid1->getXMov() * -1, 0);

        if(x2 > 0 && x2 < PathfindingWindow::xSize && y2 > 0 && y2 < PathfindingWindow::ySize)
            newAsteroid2 = createAsteroid(x2, y2, 0, asteroid2->getYMov() * -1);

    } else if(asteroid1->getYMov() != 0 && asteroid2->getXMov() != 0){
        float x1 = asteroid1->getSprite()->getPosition().x + asteroid1->getSprite()->getTextureRect().width;
        float y1 = asteroid1->getSprite()->getPosition().y;
        float x2 = asteroid1->getSprite()->getPosition().x;
        float y2 = asteroid2->getSprite()->getPosition().y - asteroid2->getSprite()->getTextureRect().height;

        if(x1 > 0 && x1 < PathfindingWindow::xSize && y1 > 0 && y1 < PathfindingWindow::ySize)
            newAsteroid1 = createAsteroid(x1, y1, asteroid1->getYMov() * -1, 0);

        if(x2 > 0 && x2 < PathfindingWindow::xSize && y2 > 0 && y2 < PathfindingWindow::ySize)
            newAsteroid2 = createAsteroid(x2, y2, 0, asteroid2->getXMov() * -1);

    }


    bool collision1 = false, collision2 = false;
    for (int i = 0; i < asteroidList.getSize(); ++i) {
        Asteroid* asteroid = asteroidList.getElement(i)->getData();
        if(newAsteroid1 != nullptr){
            newAsteroid1->update();
            if(asteroid->checkCollision(newAsteroid1)){
                collision1 = true;
            }
        }
        if(newAsteroid2 != nullptr){
            newAsteroid2->update();
            if(asteroid->checkCollision(newAsteroid2)){
                collision2 = true;
            }
        }
    }

    if(asteroidList.getSize() <= PathfindingWindow::getMaxAsteroids()){
        if(!collision1 && newAsteroid1 != nullptr)
            asteroidList.insertAtEnd(newAsteroid1);

        if(!collision2 && newAsteroid2 != nullptr)
            asteroidList.insertAtEnd(newAsteroid2);
        }
}

///Metodo para realizar el movimiento de la nave espacial
void PathfindingWindow::moveMillenniumFalcon() {
    int x = millenniumFalcon->getSprite()->getPosition().x; //Posicion en x actual
    int y = millenniumFalcon->getSprite()->getPosition().y; //Posicion en y actual
    bool move = true;

    if(current->getData()->getData() != 2){ //Mientras no se haya alcanzado el destino
        int xNext = current->getNext()->getData()->getColumnNum() * 60; //Se obtiene la posicion en x del nodo siguiente
        int yNext = current->getNext()->getData()->getRowNum() * 60; //Se obitene la posicion en y del nodo siguiente
        //std::cout <<"x: " << x << " - " << "y: " << y << " / xNext: " << xNext << " - " << "yNext: " << yNext << std::endl;


        if((x == xNext) && (y == yNext)){ //Se ha alcanzado la posicion del nodo siguiente
            Node<PfdMatrixNode<int>*>* next = current->getNext();
            LinkedList<PfdMatrixNode<int>*>* path = PathfindingA<int>::calculatePath(matrix, next->getData()->getRowNum(), next->getData()->getColumnNum(),
                                        matrix->getRows() - 1, matrix->getColumns() - 1, 10, 1000); //Se calcula el camino

            if(path->getSize() == 0) {
                move = false;
                millenniumFalcon->setYMov(0);
                millenniumFalcon->setXMov(0);
            } else{
                current = path->getElement(0);
            }
        }

        if(current->getNext() != nullptr && move) { //Mientras no se haya alcanzado el destino
            PfdMatrixNode<int> *actualNode = current->getData(); //Se obtiene el MatrixNode actual
            PfdMatrixNode<int> *nextNode = current->getNext()->getData(); //Se obtiene el MatrixNode siguiente

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
    millenniumFalcon->move(); //Se realiza el movimiento
}

///Metodo que actualiza el mapa
void PathfindingWindow::updateMap() {
    //Se colocan ceros toda la matriz
    for (int i = 0; i < matrix->getRows(); ++i) {
        for (int j = 0; j < matrix->getColumns(); ++j) {
            matrix->setElement(i, j, 0);
        }
    }

    //Se colocan los obstaculos
    for (int i = 0; i < asteroidList.getSize(); ++i) {
        Asteroid* asteroid = asteroidList.getElement(i)->getData(); //Se obtiene el asteoide

        int left = asteroid->getLeft();
        int right = asteroid->getRight();
        int top = asteroid->getTop();
        int bottom = asteroid->getBottom();
        int correction, row1, row2, column1, column2;

        correction = top % 60;
        if(correction <= 30){
            row1 = top + correction;
        } else{
            row1 = top - correction;
        }

        correction = bottom % 60;
        if(correction <= 30){
            row2 = bottom + correction;
        } else{
            row2 = bottom - correction;
        }

        correction = left % 60;
        if(correction <= 30){
            column1 = left - correction;
        } else{
            column1 = left + correction;
        }

        correction = right % 60;
        if(correction <= 30){
            column2 = right - correction;
        } else{
            column2 = right + correction;
        }

        matrix->setElement(row1 / 60, column1 / 60, 1);
        matrix->setElement(row1 / 60, column2 / 60, 1);
        matrix->setElement(row2 / 60, column1 / 60, 1);
        matrix->setElement(row2 / 60, column2 / 60, 1);
    }
}

/// Metodo que crea la matriz junto con los asteroides
/// \param maxAsteroids Numero maximo de asteroides deseados
void PathfindingWindow::createMap() {
    srand(time(NULL));

    int rows = ySize / 60; //Se obtiene el numero de filas
    int columns = xSize / 60; //Se obtiene el numero de columnas

    matrix = new PfdMatrix<int>(rows, columns); //Se crea la matriz

    //Se colocan ceros en cada posicion de la matriz
    for (int i = 0; i < matrix->getRows(); ++i) { //Se recorren las filas
        for (int j = 0; j < matrix->getColumns(); ++j) { //Se recorren las columnas
            PfdMatrixNode<int>* node = matrix->getNode(i, j); //Se obtiene el nodo en la posicion especifica
            node->setData(0); //Se coloca en cero en el nodo
        }
    }

    for (int i = 0; i < maxAsteroids; ++i) { //Se crean como una cantidad maxAsteroids de asteroides
        int x = 0 + rand() % (rows - 2); //Se obtiene una posicion random en x
        int y = 0 + rand() % (columns - 2); //Se obtiene una posicion random en y
        int num = 0 + rand() % (200); //Numero random para obtener hacia que direccion se mueve el asteroide

        if(x != 0 && y != 0){ //Si la posicion no corresponde a la casilla inicial
            if(y != (columns) - 1 || x != (rows) - 1){ //Si la posicion no corresponde a la casilla final
                Asteroid* asteroid = new Asteroid(y * 60, x * 60, 0, 0);
                asteroidList.insertAtFirst(asteroid); //Se inserta un nuevo asteroide en la casilla de asteroides
                matrix->getNode(x, y)->setData(1); //Se coloca un uno en la posicion en la matriz

                if(num <= 50){
                    asteroid->setXMov(-1);
                    std::cout << "(" << x  <<", " << y << ", -1, 0)" << std::endl;
                } else if(50 < num && num <= 100){
                    std::cout << "(" << x  <<", " << y << ", 1, 0)" << std::endl;
                    asteroid->setXMov(1);
                } else if(100 < num && num <= 150){
                    std::cout << "(" << x  <<", " << y << ", 0, -1)" << std::endl;
                    asteroid->setYMov(-1);
                } else if(150 < num && num <= 200){
                    std::cout << "(" << x  <<", " << y << ", 0, 1)" << std::endl;
                    asteroid->setYMov(1);
                }
            }
        }
    }
}

///Metodo para crear un mapa
void PathfindingWindow::createMap1() {
    matrix = new PfdMatrix<int>(12, 20); //Se crea la matriz

    //Se colocan ceros en cada posicion de la matriz
    for (int i = 0; i < matrix->getRows(); ++i) { //Se recorren las filas
        for (int j = 0; j < matrix->getColumns(); ++j) { //Se recorren las columnas
            PfdMatrixNode<int>* node = matrix->getNode(i, j); //Se obtiene el nodo en la posicion especifica
            node->setData(0); //Se coloca en cero en el nodo
        }
    }

    asteroidList.insertAtEnd(new Asteroid(15*60, 3*60, 1, 0));matrix->setElement(3, 15, 1);
    asteroidList.insertAtEnd(new Asteroid(4*60, 4*60, 0, -1));matrix->setElement(4, 4, 1);
    asteroidList.insertAtEnd(new Asteroid(8*60, 8*60, 0, -1));matrix->setElement(8, 8, 1);
    asteroidList.insertAtEnd(new Asteroid(7*60, 1*60, 0, -1));matrix->setElement(1, 7, 1);
    asteroidList.insertAtEnd(new Asteroid(6*60, 3*60, 0, 1));matrix->setElement(3, 6, 1);
    asteroidList.insertAtEnd(new Asteroid(1*60, 1*60, 0, 1));matrix->setElement(1, 1, 1);
    asteroidList.insertAtEnd(new Asteroid(17*60, 3*60, 1, 0));matrix->setElement(3, 17, 1); //
    asteroidList.insertAtEnd(new Asteroid(11*60, 8*60, 0, -1));matrix->setElement(8, 11, 1);
    asteroidList.insertAtEnd(new Asteroid(4*60, 4*60, -1, 0));matrix->setElement(4, 4, 1);
    asteroidList.insertAtEnd(new Asteroid(14*60, 9*60, 0, -1));matrix->setElement(9, 14, 1);
    asteroidList.insertAtEnd(new Asteroid(17*60, 4*60, 0, -1));matrix->setElement(4, 17, 1);
    asteroidList.insertAtEnd(new Asteroid(5*60, 3*60, 0, 1));matrix->setElement(3, 5, 1);
    asteroidList.insertAtEnd(new Asteroid(2*60, 6*60, 0, 1));matrix->setElement(6, 2, 1);
    asteroidList.insertAtEnd(new Asteroid(7*60, 1*60, 0, -1));matrix->setElement(1, 7, 1);
    asteroidList.insertAtEnd(new Asteroid(11*60, 3*60, -1, 0));matrix->setElement(3, 11, 1);
    asteroidList.insertAtEnd(new Asteroid(6*60, 3*60, -1, 0));matrix->setElement(3, 6, 1);
    asteroidList.insertAtEnd(new Asteroid(16*60, 7*60, 1, 0));matrix->setElement(7, 16, 1);
    asteroidList.insertAtEnd(new Asteroid(2*60, 1*60, 0, -1));matrix->setElement(1, 2, 1);
    asteroidList.insertAtEnd(new Asteroid(7*60, 8*60, 0, -1));matrix->setElement(8, 7, 1);
    asteroidList.insertAtEnd(new Asteroid(1*60, 8*60, 1, 0));matrix->setElement(8, 1, 1);
    asteroidList.insertAtEnd(new Asteroid(13*60, 1*60, 0, -1));matrix->setElement(1, 13, 1);
    asteroidList.insertAtEnd(new Asteroid(13*60, 5*60, 0, 1));matrix->setElement(5, 13, 1);
    asteroidList.insertAtEnd(new Asteroid(11*60, 10*60, -1, 0));matrix->setElement(10, 11, 1);
}

