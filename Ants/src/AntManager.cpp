//
// Created by d on 18/03/19.
//

#include "../include/AntManager.hpp"

#include "../include/Ant.hpp"

AntManager::AntManager(sf::RenderWindow *_ptrWindow, unsigned int _cellSizeX, unsigned int _cellSizeY) {
    this->ptrShape = new sf::RectangleShape();
    this->ptrWindow = _ptrWindow;

    this->cellSizeX = _cellSizeX;
    this->cellSizeY = _cellSizeY;

//    this->ants = std::vector<Ant*>(this->ptrWindow->getSize().x * this->ptrWindow->getSize().y);

    this->ptrShape->setSize(sf::Vector2f(cellSizeX, cellSizeY));
}

void AntManager::Update() {
    for (auto i = 0; i < 1; i++) {
        for (auto ant : alive_ants) {
            ant->Update();
        }
    }
}

void AntManager::Draw() {
    for (auto ant : alive_ants) {
        ant->Draw();
    }
}

void AntManager::AddAnt(Ant *ant) {
//    this->ants.at(CoordToIndex(ant->posX, ant->posY)) = ant;
    this->ants.push_back(ant);

    if (!ant->dead) {
        this->alive_ants.push_back(ant);
    } else {
        this->dead_ants.push_back(ant);
    }
}

Ant* AntManager::AntAt(unsigned int x, unsigned int y) {
    return this->ants.at(CoordToIndex(x, y));
}

unsigned int AntManager::CoordToIndex(unsigned int x, unsigned int y) {
    return x + y * this->ptrWindow->getSize().x;
}
