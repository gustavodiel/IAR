//
// Created by d on 18/03/19.
//

#include "../include/Ant.hpp"

#include <random>

#include "../include/EntityManager.hpp"
#include "../include/Grain.hpp"
#include "../include/Entity.hpp"

// Para Raio = 1:
// k1 = 0.01; k2 = 0.2


// Para Raio = 5:
// k1 = 0.1; k2 = 0.1

uint_fast8_t Ant::radius = 5;

double Ant::k1 = 0.1; // Pick
double Ant::k2 = 0.01; // Drop

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
    this->UpdateCarriage();
    this->MoveAnt();
}

void Ant::MoveAnt() {
  std::pair<POSITION_TYPE, POSITION_TYPE> move = this->GetNextMove();

  POSITION_TYPE newPosX = this->posX + move.first;
  POSITION_TYPE newPosY = this->posY + move.second;

  if (newPosX > this->maxX || newPosX < 0) {
    newPosX = this->posX;
  }

  if (newPosY > this->maxY || newPosY < 0) {
    newPosY = this->posY;
  }

  this->ptrEntityManager->MoveAnt(this, newPosX, newPosY);
}

void Ant::UpdateCarriage() {
  Grain* possibleGrain = this->ptrEntityManager->IsOnGrain(this->posX, this->posY);

  bool mayTakeGrain = (this->takenGrain == NULL && possibleGrain);
  bool mayDropGrain = (this->takenGrain != NULL && possibleGrain == NULL);

  if (mayTakeGrain || mayDropGrain) {
    this->CheckNeighbors();

    if (mayTakeGrain) {
      double randomNumber = this->realDistribution(this->randomMachine);
      double chance = this->ProbabilityOfPickingUp();
      // printf("PICK For %u blocks out of %i, prob is %lf\n", this->suroundGrains.size(), this->totalSuroundBlocks, chance);

      if (randomNumber < chance) {
        possibleGrain->taken = true;
        this->ptrEntityManager->RemoveGrainFromMap(possibleGrain);
        this->takenGrain = possibleGrain;
      }
    } else {
      double randomNumber = this->realDistribution(this->randomMachine);
      double chance = this->ProbabilityOfDropping();
      // printf("DROP For %u blocks out of %i, prob is %lf\n", this->suroundGrains.size(), this->totalSuroundBlocks, chance);

      if (randomNumber < chance) {
        this->takenGrain->taken = false;
        this->takenGrain->posX = this->posX;
        this->takenGrain->posY = this->posY;
        this->ptrEntityManager->ReplaceGrainOnMap(this->takenGrain);

        this->takenGrain = NULL;
      }
    }
  }
}

std::pair<POSITION_TYPE, POSITION_TYPE> Ant::GetNextMove() {

    return std::make_pair(this->integerDistribution(this->randomMachine), this->integerDistribution(this->randomMachine));
}

void Ant::CheckNeighbors() {
	auto grainResult = this->ptrEntityManager->GetGrainsInRadius(this->posX, this->posY, this->radius);

	// this->suroundAnts = this->ptrEntityManager->GetAntsInRadius(this->posX, this->posY, this->radius);
	this->suroundGrains = grainResult.first;

	this->totalSuroundBlocks = grainResult.second;
}

double Ant::SumFOfX() {
    double totalDead = (double) this->suroundGrains.size();

    // int mainNumber = this->totalSuroundBlocks;
    int blockSize = (2 * this->radius + 1);
    int mainNumber = (blockSize * blockSize - 1);
    double radiusTotal = mainNumber;

    return totalDead / (radiusTotal * radiusTotal);
}

double Ant::ProbabilityOfPickingUp() {
    double sumOfX = this->SumFOfX();
    double chance = this->k1 / (this->k1 + sumOfX);

    return chance * chance;
}

double Ant::ProbabilityOfDropping() {
    double sumOfX = this->SumFOfX();
    double chance = sumOfX / (this->k2 + sumOfX);

    return chance * chance;
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
