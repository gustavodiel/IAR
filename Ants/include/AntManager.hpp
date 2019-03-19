//
// Created by d on 18/03/19.
//

#ifndef ANTS_ANTMANAGER_HPP
#define ANTS_ANTMANAGER_HPP

#include <vector>
#include <SFML/Graphics.hpp>


class AntManager {

public:
    unsigned int cellSizeX, cellSizeY;

    std::vector<class Ant*>       ants;

    sf::RectangleShape      *ptrShape;

    sf::RenderWindow        *ptrWindow;

    AntManager(sf::RenderWindow*, unsigned int, unsigned int);

    void AddAnt(class Ant*);
    void Update();
    void Draw();

    Ant* AntAt(unsigned int, unsigned int);

    unsigned int CoordToIndex(unsigned int, unsigned int);

};


#endif //ANTS_ANTMANAGER_HPP
