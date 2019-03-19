//
// Created by d on 18/03/19.
//

#include "../include/Ant.hpp"

Ant::Ant(AntManager * _ptrAntManager, unsigned int x, unsigned int y) {
    this->ptrAntManager = _ptrAntManager;

    this->posX = x;
    this->posY = y;
}


void Ant::Update() {
//    this->posX += 1;
}

void Ant::Draw() {
    this->ptrAntManager->ptrShape->setFillColor(sf::Color::Green);
    this->ptrAntManager->ptrShape->setPosition(this->posX, this->posY);

    this->ptrAntManager->ptrWindow->draw(*this->ptrAntManager->ptrShape);
}
