#include "../include/Grain.hpp"

#include "../include/EntityManager.hpp"
#include "../include/Entity.hpp"

Grain::Grain(EntityManager * ptrEntityManager, POSITION_TYPE x, POSITION_TYPE y, int size, int weight) {
    this->ptrEntityManager = ptrEntityManager;

    this->taken = false;

    this->size = size;
    this->weight = weight;

    this->posX = x;
    this->posY = y;
}

void Grain::Update() {
}

void Grain::Draw() {
    if (this->taken) {
        return;
    }

    this->ptrEntityManager->ptrShape->setFillColor(sf::Color::Yellow);

    this->ptrEntityManager->ptrShape->setPosition(this->posX, this->posY);

    this->ptrEntityManager->ptrWindow->draw(*this->ptrEntityManager->ptrShape);
}