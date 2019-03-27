//
// Created by d on 18/03/19.
//

#include "../include/Application.hpp"

#include "../include/EntityManager.hpp"
#include "../include/Ant.hpp"
#include "../include/Grain.hpp"

Application::Application(MAP_TYPE _x, MAP_TYPE _y) :
    windowX(_x), windowY(_y) { }

void Application::Start() {
    this->ptrWindow = new sf::RenderWindow(sf::VideoMode(windowX, windowY), "Inteligencia Artificial - Ants");

//    this->ptrWindow->setFramerateLimit(60);

    EntityManager* entityManager = new EntityManager(this->ptrWindow, 1, 1);
    
    int num_ants = 5000;
    int num_grains = 10000;

    for (auto i = 0; i < num_ants; i++) {
        std::pair<POSITION_TYPE, POSITION_TYPE> position = entityManager->GetValidAntPosition();
        
        entityManager->AddAnt(new Ant(entityManager, position.first, position.second));
    }

    for (auto i = 0; i < num_grains; i++) {
        std::pair<POSITION_TYPE, POSITION_TYPE> position = entityManager->GetValidGrainPosition();
        
        entityManager->AddGrain(new Grain(entityManager, position.first, position.second, 1, 1));
    }

    while (this->ptrWindow->isOpen())
    {
        sf::Event event;
        while (this->ptrWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->ptrWindow->close();
        }

        this->ptrWindow->clear();

        entityManager->Update();
        entityManager->Draw();

        this->ptrWindow->display();
    }

}

void Application::ProcessLoop() {

}
