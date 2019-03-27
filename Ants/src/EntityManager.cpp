//
// Created by d on 18/03/19.
//

#include "../include/EntityManager.hpp"

#include <random>

#include "../include/Ant.hpp"
#include "../include/Grain.hpp"

EntityManager::EntityManager(sf::RenderWindow *_ptrWindow, MAP_TYPE _cellSizeX, MAP_TYPE _cellSizeY) {
    this->ptrShape = new sf::RectangleShape();
    this->ptrWindow = _ptrWindow;

    this->cellSizeX = _cellSizeX;
    this->cellSizeY = _cellSizeY;

    this->maxX = this->ptrWindow->getSize().x;
    this->maxY = this->ptrWindow->getSize().y;

    this->antsMatrix = (Ant***) malloc(sizeof(Ant**) * this->ptrWindow->getSize().x);
    this->grainsMatrix = (Grain***) malloc(sizeof(Grain**) * this->ptrWindow->getSize().x);

    // Change to one unique array! See OPRP
    for (auto i = 0; i < this->ptrWindow->getSize().x; ++i) {

        this->antsMatrix[i] = (Ant**) malloc(sizeof(Ant*) * this->ptrWindow->getSize().y);
        this->grainsMatrix[i] = (Grain**) malloc(sizeof(Grain*) * this->ptrWindow->getSize().y);

        for (auto j = 0; j < this->ptrWindow->getSize().y; ++j) {
            this->antsMatrix[i][j] = NULL;
            this->grainsMatrix[i][j] = NULL;
        }
    }

    this->ptrShape->setSize(sf::Vector2f(cellSizeX, cellSizeY));
}

void EntityManager::Update() {
    for (auto i = 0; i < 50; i++) {
        // for (const auto& grain : grains) {
        //     grain->Update();
        // }

        for (const auto& ant : ants) {
            ant->Update();
        }
    }
}

void EntityManager::Draw() {
    for (const auto& ant : ants) {
        ant->Draw();
    }

    for (const auto& grain : grains) {
        grain->Draw();
    }
}

void EntityManager::AddAnt(Ant *ant) {
    this->ants.push_back(ant);

    this->antsMatrix[ant->posX][ant->posY] = ant;
}

void EntityManager::MoveAnt(Ant *ant, POSITION_TYPE newX, POSITION_TYPE newY) {
    if (this->IsOnAnt(newX, newY) != NULL) {
        return;
    }
    this->antsMatrix[newX][newY] = ant;
    this->antsMatrix[ant->posX][ant->posY] = NULL;

    ant->posX = newX;
    ant->posY = newY;
}

void EntityManager::AddGrain(Grain *grain) {
    this->grains.push_back(grain);

    this->grainsMatrix[grain->posX][grain->posY] = grain;
}

void EntityManager::MoveGrain(Grain *grain, POSITION_TYPE newX, POSITION_TYPE newY) {
    this->grainsMatrix[newX][newY] = grain;
    this->grainsMatrix[grain->posX][grain->posY] = NULL;

    grain->posX = newX;
    grain->posY = newY;
}

std::vector<Grain*> EntityManager::GetGrainsInRadius(POSITION_TYPE posX, POSITION_TYPE posY, uint8_t radius) {
    std::vector<Grain*> entities;
    for (auto i = -radius; i <= radius; i++) {
        for (auto j = -radius; j <= radius; j++) {
            POSITION_TYPE findX = posX + i;
            POSITION_TYPE findY = posY + j;

            if (!this->LocationIsValid(findX, findY)){
                continue;
            }

            Grain* possible = this->grainsMatrix[posX + i][posY + j];
            if (possible != NULL) {
                entities.push_back(possible);
            }
        }
    }
    return entities;
}

std::vector<Ant*> EntityManager::GetAntsInRadius(POSITION_TYPE posX, POSITION_TYPE posY, uint8_t radius) {
    std::vector<Ant*> entities;
    for (auto i = -radius; i <= radius; i++) {
        for (auto j = -radius; j <= radius; j++) {
            POSITION_TYPE findX = posX + i;
            POSITION_TYPE findY = posY + j;

            if (!this->LocationIsValid(findX, findY)){
                continue;
            }

            Ant* possible = this->antsMatrix[posX + i][posY + j];
            if (possible != NULL) {
                entities.push_back(possible);
            }
        }
    }
    return entities;
}

bool EntityManager::LocationIsValid(POSITION_TYPE x, POSITION_TYPE y) {
    POSITION_TYPE minX = 0;
    POSITION_TYPE minY = 0;

    return ((x < maxX) && (x >= minX) && (y < maxY) && (y >= minY));
}

Ant* EntityManager::IsOnAnt(POSITION_TYPE x, POSITION_TYPE y) {
    if (!this->LocationIsValid(x, y)){
        return NULL;
    }

    Ant* possible = this->antsMatrix[x][y];
    if (possible != NULL) {
        return possible;
    }

    return NULL;
}

Grain* EntityManager::IsOnGrain(POSITION_TYPE x, POSITION_TYPE y) {
    if (!this->LocationIsValid(x, y)){
        return NULL;
    }

    Grain* possible = this->grainsMatrix[x][y];
    if (possible != NULL) {
        return possible;
    }

    return NULL;
}

std::pair<POSITION_TYPE, POSITION_TYPE> EntityManager::GetValidAntPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    POSITION_TYPE x = dist(mt) * this->maxX;
    POSITION_TYPE y = dist(mt) * this->maxY;

    while (this->IsOnAnt(x, y) != NULL) {
        x = dist(mt) * this->maxX;
        y = dist(mt) * this->maxY;
    }

    return std::make_pair(x, y);
}

std::pair<POSITION_TYPE, POSITION_TYPE> EntityManager::GetValidGrainPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    POSITION_TYPE x = dist(mt) * this->maxX;
    POSITION_TYPE y = dist(mt) * this->maxY;

    while (this->IsOnGrain(x, y) != NULL) {
        x = dist(mt) * this->maxX;
        y = dist(mt) * this->maxY;
    }

    return std::make_pair(x, y);
}

void EntityManager::RemoveGrainFromMap(Grain* grain) {
    this->grainsMatrix[grain->posX][grain->posY] = NULL;
}

void EntityManager::ReplaceGrainOnMap(Grain* grain) {
    this->grainsMatrix[grain->posX][grain->posY] = grain;
}

Ant* EntityManager::AntAt(POSITION_TYPE x, POSITION_TYPE y) {
    return this->ants.at(CoordToIndex(x, y));
}

MAP_TYPE EntityManager::CoordToIndex(POSITION_TYPE x, POSITION_TYPE y) {
    return x + y * this->ptrWindow->getSize().x;
}
