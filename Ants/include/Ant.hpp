//
// Created by d on 18/03/19.
//

#ifndef ANTS_ANT_HPP
#define ANTS_ANT_HPP

#include <random>

#include "Defines.hpp"
#include "Entity.hpp"

class Ant : public Entity {
public:
    Ant(EntityManager*, POSITION_TYPE, POSITION_TYPE);

    POSITION_TYPE maxX, maxY;

    Grain* takenGrain;

    std::mt19937 mt;
    std::uniform_int_distribution<POSITION_TYPE> dist;

    std::vector<Ant*> suroundAnts;
    std::vector<Grain*> suroundGrains;

    uint8_t radius = 1;
    
    void Update();
    void Draw();

    double SumFOfX();
    double ProbabilityOfPickingUp();
    double ProbabilityOfDropping();

    void CheckNeighbors();

    std::pair<POSITION_TYPE, POSITION_TYPE> GetNextMove();
};


#endif //ANTS_ANT_HPP
