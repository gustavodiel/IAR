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

	uint8_t totalSuroundBlocks;

    POSITION_TYPE maxX, maxY;

    Grain* takenGrain;

	std::mt19937 randomMachine;
	std::uniform_int_distribution<POSITION_TYPE> integerDistribution;
	std::uniform_real_distribution<double> realDistribution;

    std::vector<Ant*> suroundAnts;
    std::vector<Grain*> suroundGrains;

    static uint8_t radius;
    static double k1;
    static double k2;

    void Update();
    void Draw();

    double SumFOfX();
    double ProbabilityOfPickingUp();
    double ProbabilityOfDropping();

    void UpdateCarriage();
    void MoveAnt();

    void CheckNeighbors();

    std::pair<POSITION_TYPE, POSITION_TYPE> GetNextMove();
};


#endif //ANTS_ANT_HPP
