#include "../include/Grain.hpp"

#include "../include/EntityManager.hpp"
#include "../include/Entity.hpp"

Grain::Grain(EntityManager * ptrEntityManager, POSITION_TYPE x, POSITION_TYPE y, int size, int weight) {
    this->ptrEntityManager = ptrEntityManager;

    this->taken = false;
	this->onSight = false;

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

	if (onSight) {
		this->ptrEntityManager->ptrRectangleShape->setFillColor(sf::Color::Red);
		onSight = false;
	}
	else {
		this->ptrEntityManager->ptrRectangleShape->setFillColor(sf::Color::Yellow);
	}

	this->ptrEntityManager->ptrRectangleShape->setPosition(this->posX * this->ptrEntityManager->cellSizeX, this->posY * this->ptrEntityManager->cellSizeY);

    this->ptrEntityManager->ptrWindow->draw(*this->ptrEntityManager->ptrRectangleShape);
}