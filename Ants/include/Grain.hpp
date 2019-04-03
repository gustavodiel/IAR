//
// Created by d on 18/03/19.
//

#ifndef GRAIN_HPP
#define GRAIN_HPP

#include "Entity.hpp"
#include "Defines.hpp"

class Grain : public Entity {
public:
    int size, weight;
    bool taken;
	bool onSight;

    Grain(EntityManager * ptrEntityManager, POSITION_TYPE x, POSITION_TYPE y, int size, int weight);

    void Update();
    void Draw();
};

#endif // GRAIN_HPP