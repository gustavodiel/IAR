//
// Created by d on 18/03/19.
//

#include "../include/Application.hpp"
#include "../include/AntManager.hpp"
#include "../include/Ant.hpp"

Application::Application(unsigned int _x, unsigned int _y) :
    windowX(_x), windowY(_y) { }

void Application::Start() {
    this->ptrWindow = new sf::RenderWindow(sf::VideoMode(windowX, windowY), "SFML works!");

//    this->ptrWindow->setFramerateLimit(60);

    AntManager* antManager = new AntManager(this->ptrWindow, 1, 1);

    for (auto i = 0; i < this->ptrWindow->getSize().x; i++) {
        for (auto j = 0; j < this->ptrWindow->getSize().y; j++) {
            if (rand() % 100 < 3)
                antManager->AddAnt(new Ant(antManager, i, j));
        }
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

        antManager->Update();
        antManager->Draw();

        this->ptrWindow->display();
    }

}

void Application::ProcessLoop() {

}
