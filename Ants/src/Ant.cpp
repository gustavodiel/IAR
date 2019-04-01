//
// Created by d on 18/03/19.
//

#include "../include/Ant.hpp"

#include <random>

#include "../include/EntityManager.hpp"
#include "../include/Grain.hpp"
#include "../include/Entity.hpp"

Ant::Ant(EntityManager * ptrEntityManager, POSITION_TYPE x, POSITION_TYPE y) {
    this->ptrEntityManager = ptrEntityManager;

    this->posX = x;
    this->posY = y;

    std::random_device rd;
	randomMachine = std::mt19937(rd());
	integerDistribution = std::uniform_int_distribution<POSITION_TYPE>(-1, 1);
	realDistribution = std::uniform_real_distribution<double>(0.0, 1.0);

    this->takenGrain = NULL;

    this->maxX = this->ptrEntityManager->amountCellsWidth - 1;
    this->maxY = this->ptrEntityManager->amountCellsHeight - 1;
}

void Ant::Update() {
	std::pair<POSITION_TYPE, POSITION_TYPE> move = this->GetNextMove();

	POSITION_TYPE newPosX = this->posX + move.first;
	POSITION_TYPE newPosY = this->posY + move.second;

	bool isOnGrain = this->ptrEntityManager->IsOnGrain(newPosX, newPosY) && this->takenGrain != NULL;

	if (isOnGrain || newPosX > this->maxX || newPosX < 0) {
		newPosX = this->posX;
	}

	if (isOnGrain || newPosY > this->maxY || newPosY < 0) {
		newPosY = this->posY;
	}

	Grain* possibleGrain = this->ptrEntityManager->IsOnGrain(newPosX, newPosY);

	bool mayTakeGrain = (this->takenGrain == NULL && possibleGrain);
	bool mayDropGrain = (this->takenGrain != NULL && !this->ptrEntityManager->IsOnEntity(newPosX, newPosY));

	if (mayTakeGrain || mayDropGrain) {
		this->CheckNeighbors();

		if (mayTakeGrain) {
			if (this->realDistribution(this->randomMachine) < this->ProbabilityOfPickingUp()) {
				possibleGrain->taken = true;
				this->ptrEntityManager->RemoveGrainFromMap(possibleGrain);
				this->takenGrain = possibleGrain;
			}
		} else {
			if (this->realDistribution(this->randomMachine) < this->ProbabilityOfDropping()) {

				this->takenGrain->taken = false;
				this->takenGrain->posX = this->posX;
				this->takenGrain->posY = this->posY;
				this->ptrEntityManager->ReplaceGrainOnMap(this->takenGrain);

				this->takenGrain = NULL;
			}
		}
	}


	this->ptrEntityManager->MoveAnt(this, newPosX, newPosY);
}

std::pair<POSITION_TYPE, POSITION_TYPE> Ant::GetNextMove() {

    return std::make_pair(this->integerDistribution(this->randomMachine), this->integerDistribution(this->randomMachine));
}

void Ant::CheckNeighbors() {
	auto grainResult = this->ptrEntityManager->GetGrainsInRadius(this->posX, this->posY, this->radius);

	this->suroundAnts = this->ptrEntityManager->GetAntsInRadius(this->posX, this->posY, this->radius);
	this->suroundGrains = grainResult.first;

	this->totalSuroundBlocks = grainResult.second;
}

double Ant::SumFOfX() {
    double totalDead = (double) this->suroundGrains.size();
    double radiusTotal = this->radius * this->radius;

    return totalDead / (radiusTotal * radiusTotal);
}

double Ant::ProbabilityOfPickingUp() {
    double avgSuround = this->SumFOfX();
    double k1 = 0.5;
    double finalCount = k1 / (k1 + avgSuround);

    return finalCount;
}

double Ant::ProbabilityOfDropping() {
    double avgSuround = this->SumFOfX();
    double k2 = 0.5;
    double finalCount = avgSuround / (k2 + avgSuround);

    return finalCount;
}

void Ant::Draw() {
	static bool debug = false;

	float posX = this->posX * this->ptrEntityManager->cellSizeX;
	float posY = this->posY * this->ptrEntityManager->cellSizeY;

    if (this->takenGrain != NULL) {
        this->ptrEntityManager->ptrRectangleShape->setFillColor(sf::Color::Green);
    } else {
        this->ptrEntityManager->ptrRectangleShape->setFillColor(sf::Color::Blue);
    }
    this->ptrEntityManager->ptrRectangleShape->setPosition(posX, posY);

    this->ptrEntityManager->ptrWindow->draw(*this->ptrEntityManager->ptrRectangleShape);


	if (debug) {
		float radius = (this->radius + 1) * this->ptrEntityManager->cellSizeX;

		this->ptrEntityManager->ptrCircleShape->setFillColor(sf::Color(255, 0, 0, 10));

		this->ptrEntityManager->ptrCircleShape->setRadius(radius);

		this->ptrEntityManager->ptrCircleShape->setPosition(posX, posY);
		this->ptrEntityManager->ptrCircleShape->setOrigin(radius, radius);

		this->ptrEntityManager->ptrWindow->draw(*this->ptrEntityManager->ptrCircleShape);
	}
}