//
// Created by d on 18/03/19.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Defines.hpp"
#include "EntityManager.hpp"

class Entity {
public:
    POSITION_TYPE posX, posY;

    EntityManager      *ptrEntityManager;

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif // ENTITY_HPP