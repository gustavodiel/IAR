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

    this->ants.reserve(this->ptrWindow->getSize().x * this->ptrWindow->getSize().y);

    this->ptrShape->setSize(sf::Vector2f(cellSizeX, cellSizeY));
}

void AntManager::Update() {
    for (auto ant : ants) {
        ant->Update();
    }
}

void AntManager::Draw() {
    for (auto ant : ants) {
        ant->Draw();
    }
}

void AntManager::AddAnt(Ant *ant) {
    int index = CoordToIndex(ant->posX, ant->posY);

    this->ants.insert(this->ants.begin() + index, ant);
}

Ant* AntManager::AntAt(unsigned int x, unsigned int y) {
    return this->ants.at(CoordToIndex(x, y));
}

unsigned int AntManager::CoordToIndex(unsigned int x, unsigned int y) {
    return x + y * this->ptrWindow->getSize().x;
}
