//
// Created by fabian on 11/10/17.
//

#ifndef MILLENNIUMFALCONSIMULATION_ASTEROID_H
#define MILLENNIUMFALCONSIMULATION_ASTEROID_H

#include <SFML/Graphics.hpp>
#include <vector>

///Class of Asteroid
class Asteroid
{
public:
    sf::Sprite asteroid;
    float bottom, left, right, top;

    std::vector<std::vector<bool>> mask;

    ///Constructor method of asteroid class
    Asteroid(sf::Vector2f position, sf::Texture &texture)
    {
        sf::Image image;
        image = texture.copyToImage();

        for(int i = 0; i < image.getSize().x; i++)
        {
            std::vector<bool> tempMask;
            for (int j = 0; j < image.getSize().y; j++) {
                if (image.getPixel(i, j).a > 0)
                    tempMask.push_back(true);
                else
                    tempMask.push_back(false);
            }
            mask.push_back(tempMask);
        }
        asteroid.setTexture(texture);
        asteroid.setPosition(position);
        asteroid.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    ///Method that updates the position of the object on screen
    void Update()
    {
        bottom = asteroid.getPosition().y + asteroid.getTextureRect().height;
        left = asteroid.getPosition().x;
        right = asteroid.getPosition().x + asteroid.getTextureRect().width;
        top = asteroid.getPosition().y;
    }

    ///Method that verifies if the object collide with another object
    bool Collision(Asteroid &ast)
    {
        if(right <= ast.left || left >= ast.right ||
           top >= ast.bottom || bottom <= ast.top) {
        }else{
            float colBottom, colTop, colLeft, colRight;
            colBottom = std::min(bottom, ast.bottom);
            colTop = std::max(top, ast.top);
            colLeft = std::max(left, ast.left);
            colRight = std::min(right, ast.right);

            for (int i = colTop; i < colBottom; i++) {
                for (int j = colLeft; j < colRight; j++) {
                    if (mask[j - left][i - top] && ast.mask[j - ast.left][i - ast.top])
                        return true;
                }
            }
        }
        return false;
    }

    void Move(char m)
    {
        switch(m)
        {
            //Right
            case 'r':
                asteroid.move(1.0f,0);
                break;
            //Left
            case 'l':
                asteroid.move(-1.0f,0);
                break;
            //Up
            case 'u':
                asteroid.move(0,-1.0f);
                break;
            //Down
            case 'd':
                asteroid.move(0,1.0f);
                break;
            default:
                std::cout << "No Movement" << std::endl;
                break;
        }
    }
};

#endif //MILLENNIUMFALCONSIMULATION_ASTEROID_H
