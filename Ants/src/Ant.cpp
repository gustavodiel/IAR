//
// Created by d on 18/03/19.
//

#include "../include/Ant.hpp"

Ant::Ant(AntManager * _ptrAntManager, unsigned int x, unsigned int y) {
    this->ptrAntManager = _ptrAntManager;

    this->dead = false;

    this->posX = x;
    this->posY = y;
}


void Ant::Update() {
    int velX = 0;
    int velY = 0;

    if (rand() % 100 < 30) {
        velX = -1;
    } else if (rand() % 100 < 80) {
        velX = 1;
    }

    if (rand() % 100 < 30) {
        velY = -1;
    } else if (rand() % 100 < 30) {
        velY = 1;
    }

    this->posX += velX;
    this->posY += velY;

    if (this->posX >= this->ptrAntManager->ptrWindow->getSize().x) {
        this->posX = 0;
    }

    if (this->posX < 0) {
        this->posX = this->ptrAntManager->ptrWindow->getSize().x - 1;
    }

    if (this->posY >= this->ptrAntManager->ptrWindow->getSize().y) {
        this->posY = 0;
    }

    if (this->posY < 0) {
        this->posY = this->ptrAntManager->ptrWindow->getSize().y - 1;
    }
}

void Ant::Draw() {
    this->ptrAntManager->ptrShape->setFillColor(sf::Color::Green);
    this->ptrAntManager->ptrShape->setPosition(this->posX, this->posY);

    this->ptrAntManager->ptrWindow->draw(*this->ptrAntManager->ptrShape);
}
