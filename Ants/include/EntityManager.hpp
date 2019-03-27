//
// Created by d on 18/03/19.
//

#ifndef ANTS_ENTITYMANAGER_HPP
#define ANTS_ENTITYMANAGER_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "Defines.hpp"

class EntityManager {

public:
    MAP_TYPE cellSizeX, cellSizeY;
    POSITION_TYPE maxX, maxY;

    std::vector<class Ant*>         ants;
    std::vector<class Grain*>       grains;

    class Ant***                    antsMatrix;
    class Grain***                  grainsMatrix;

    sf::RectangleShape      *ptrShape;

    sf::RenderWindow        *ptrWindow;

    EntityManager(sf::RenderWindow*, POSITION_TYPE, POSITION_TYPE);

    void AddAnt(Ant*);
    void MoveAnt(Ant*, POSITION_TYPE, POSITION_TYPE);

    void AddGrain(Grain*);
    void MoveGrain(Grain*, POSITION_TYPE, POSITION_TYPE);

    std::vector<Grain*> GetGrainsInRadius(POSITION_TYPE, POSITION_TYPE, uint8_t);
    std::vector<Ant*> GetAntsInRadius(POSITION_TYPE, POSITION_TYPE, uint8_t);

    bool LocationIsValid(POSITION_TYPE x, POSITION_TYPE y);
    Ant* IsOnAnt(POSITION_TYPE x, POSITION_TYPE y);
    Grain* IsOnGrain(POSITION_TYPE x, POSITION_TYPE y);

    void RemoveGrainFromMap(Grain*);
    void ReplaceGrainOnMap(Grain*);

    std::pair<POSITION_TYPE, POSITION_TYPE> GetValidAntPosition();
    std::pair<POSITION_TYPE, POSITION_TYPE> GetValidGrainPosition();

    void Update();
    void Draw();

    Ant* AntAt(POSITION_TYPE, POSITION_TYPE);

    MAP_TYPE CoordToIndex(POSITION_TYPE, POSITION_TYPE);
};


#endif //ANTS_ENTITYMANAGER_HPP
