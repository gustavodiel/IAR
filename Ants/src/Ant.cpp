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
    mt = std::mt19937(rd());
    dist = std::uniform_int_distribution<POSITION_TYPE>(-1, 1);

    this->takenGrain = NULL;

    this->maxX = this->ptrEntityManager->ptrWindow->getSize().x - 1;
    this->maxY = this->ptrEntityManager->ptrWindow->getSize().y - 1;
}

void Ant::Update() {
    this->CheckNeighbors();

    std::pair<POSITION_TYPE, POSITION_TYPE> move = this->GetNextMove();

    POSITION_TYPE newPosX = this->posX + move.first;
    POSITION_TYPE newPosY = this->posY + move.second;

    if (newPosX > this->maxX || newPosX < 0) {
        newPosX = this->posX;
    }

    if (newPosY > this->maxY || newPosY < 0) {
        newPosY = this->posY;
    }

    // ProcessCurrentPlace
    {
        if (this->takenGrain == NULL) {
            if (this->dist(this->mt) < this->ProbabilityOfPickingUp()) {
                Grain* grain = this->ptrEntityManager->IsOnGrain(newPosX, newPosY);
                if (grain != nullptr) {
                    grain->taken = true;
                    this->ptrEntityManager->RemoveGrainFromMap(grain);
                    this->takenGrain = grain;
                }
            }

        } else {
            if (this->dist(this->mt) < this->ProbabilityOfDropping()) {
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

    return std::make_pair(dist(mt), dist(mt));
}

void Ant::CheckNeighbors() {
    this->suroundGrains = this->ptrEntityManager->GetGrainsInRadius(this->posX, this->posY, this->radius);
    this->suroundAnts = this->ptrEntityManager->GetAntsInRadius(this->posX, this->posY, this->radius);
}

double Ant::SumFOfX() {
    double totalDead = this->suroundGrains.size();
    double radiusTotal = this->radius * this->radius;

    return totalDead / (radiusTotal * radiusTotal);
}

double Ant::ProbabilityOfPickingUp() {
    double avgSuround = this->SumFOfX();
    double k1 = 0.5;
    double finalCount = k1 / (k1 + avgSuround);

    return finalCount * finalCount;

}

double Ant::ProbabilityOfDropping() {
    double avgSuround = this->SumFOfX();
    double k2 = 0.5;
    double finalCount = avgSuround / (k2 + avgSuround);

    return finalCount * finalCount;
}

void Ant::Draw() {
    if (this->takenGrain != NULL) {
        this->ptrEntityManager->ptrShape->setFillColor(sf::Color::Green);
    } else {
        this->ptrEntityManager->ptrShape->setFillColor(sf::Color::Blue);
    }
    this->ptrEntityManager->ptrShape->setPosition(this->posX, this->posY);

    this->ptrEntityManager->ptrWindow->draw(*this->ptrEntityManager->ptrShape);
}