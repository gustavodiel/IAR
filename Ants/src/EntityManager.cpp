//
// Created by d on 18/03/19.
//

#include "../include/EntityManager.hpp"

#include <random>

#include "../include/Ant.hpp"
#include "../include/Grain.hpp"

EntityManager::EntityManager(sf::RenderWindow *_ptrWindow, MAP_TYPE _cellSizeX, MAP_TYPE _cellSizeY) {
    this->ptrRectangleShape = new sf::RectangleShape();
    this->ptrCircleShape = new sf::CircleShape();

    this->ptrWindow = _ptrWindow;

    this->cellSizeX = _cellSizeX;
    this->cellSizeY = _cellSizeY;

    this->windowsWidth = this->ptrWindow->getSize().x;
    this->windowsHeight = this->ptrWindow->getSize().y;

    this->amountCellsWidth = this->windowsWidth / this->cellSizeX;
    this->amountCellsHeight = this->windowsHeight / this->cellSizeY;

    this->antsMatrix = (Ant***) malloc(sizeof(Ant**) * this->amountCellsWidth);
    this->grainsMatrix = (Grain***) malloc(sizeof(Grain**) * this->amountCellsWidth);

    // Change to one unique array! See OPRP
    for (auto i = 0; i < this->amountCellsWidth; ++i) {

        this->antsMatrix[i] = (Ant**) malloc(sizeof(Ant*) * this->amountCellsHeight);
        this->grainsMatrix[i] = (Grain**) malloc(sizeof(Grain*) * this->amountCellsHeight);

        for (auto j = 0; j < this->amountCellsHeight; ++j) {
            this->antsMatrix[i][j] = NULL;
            this->grainsMatrix[i][j] = NULL;
        }
    }

    this->ptrRectangleShape->setSize(sf::Vector2f(cellSizeX, cellSizeY));
}

void EntityManager::Update() {
    for (auto i = 0; i < 100; i++) {
		for (const auto& ant : ants) {
            ant->Update();
        }
    }
}

void EntityManager::Draw() {
    if (drawGrains)
        for (const auto& grain : grains) {
            grain->Draw();
        }

    if (drawAnts)
        for (const auto& ant : ants) {
                ant->Draw();
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

std::pair<std::vector<Grain*>, int> EntityManager::GetGrainsInRadius(POSITION_TYPE posX, POSITION_TYPE posY, uint8_t radius) {
    std::vector<Grain*> entities;
    int total = 0;

    POSITION_TYPE findX;
    POSITION_TYPE findY;

    for (auto i = -radius; i <= radius; i++) {
        for (auto j = -radius; j <= radius; j++) {
            findX = posX + i;
            findY = posY + j;

            if (!this->LocationIsValid(findX, findY)){
                continue;
            }

            total++;

            Grain* possible = this->grainsMatrix[findX][findY];
            if (possible != NULL) {
                // possible->onSight = true;
                entities.push_back(possible);
            }
        }
    }

    return make_pair(entities, total);
}

std::vector<Ant*> EntityManager::GetAntsInRadius(POSITION_TYPE posX, POSITION_TYPE posY, uint8_t radius) {
    std::vector<Ant*> entities;

		POSITION_TYPE findX;
		POSITION_TYPE findY;

    for (auto i = -radius; i <= radius; i++) {
        for (auto j = -radius; j <= radius; j++) {
						findX = posX + i;
            findY = posY + j;

            if (!this->LocationIsValid(findX, findY) || (i == 0 && j == 0)){
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
    return ((x < this->amountCellsWidth) && (x >= 0) && (y < this->amountCellsHeight) && (y >= 0));
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

    POSITION_TYPE x = dist(mt) * this->amountCellsWidth;
		POSITION_TYPE y = dist(mt) * this->amountCellsHeight;

    while (this->IsOnAnt(x, y) != NULL) {
        x = dist(mt) * this->amountCellsWidth;
        y = dist(mt) * this->amountCellsHeight;
    }

    return std::make_pair(x, y);
}

std::pair<POSITION_TYPE, POSITION_TYPE> EntityManager::GetValidGrainPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

		POSITION_TYPE x = dist(mt) * this->amountCellsWidth;
		POSITION_TYPE y = dist(mt) * this->amountCellsHeight;

    while (this->IsOnGrain(x, y) != NULL) {
		x = dist(mt) * this->amountCellsWidth;
		y = dist(mt) * this->amountCellsHeight;
    }

    return std::make_pair(x, y);
}

void EntityManager::RemoveGrainFromMap(Grain* grain) {
    this->grainsMatrix[grain->posX][grain->posY] = NULL;
}

void EntityManager::ReplaceGrainOnMap(Grain* grain) {
    this->grainsMatrix[grain->posX][grain->posY] = grain;
}

bool EntityManager::IsOnEntity(POSITION_TYPE x, POSITION_TYPE y) {
		if (!this->LocationIsValid(x, y)) {
				return false;
		}

		if (this->grainsMatrix[x][y] != NULL || this->antsMatrix[x][y] != NULL) {
				return true;
		}

		return false;
}
