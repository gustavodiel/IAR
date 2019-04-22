//
// Created by d on 18/03/19.
//

#include "../include/Application.hpp"

#include <sstream>

#include "../include/EntityManager.hpp"
#include "../include/Ant.hpp"
#include "../include/Grain.hpp"

Application::Application(MAP_TYPE _x, MAP_TYPE _y) :
    windowX(_x), windowY(_y) { }

void Application::Start() {
    this->ptrWindow = new sf::RenderWindow(sf::VideoMode(windowX, windowY), "Inteligencia Artificial - Ants");

    // this->ptrWindow->setFramerateLimit(5);

    int cellSizeX = 5;
    int cellSizeY = 5;

    EntityManager* entityManager = new EntityManager(this->ptrWindow, cellSizeX, cellSizeY);

    int cellsWidth = this->ptrWindow->getSize().x / cellSizeX;
    int cellsHeight = this->ptrWindow->getSize().y / cellSizeY;

    int num_ants = cellsWidth * cellsHeight * 0.05;
    int num_grains = cellsWidth * cellsHeight * 0.2;

    for (auto i = 0; i < num_ants; i++) {
        std::pair<POSITION_TYPE, POSITION_TYPE> position = entityManager->GetValidAntPosition();

        entityManager->AddAnt(new Ant(entityManager, position.first, position.second));
    }

    for (auto i = 0; i < num_grains; i++) {
        std::pair<POSITION_TYPE, POSITION_TYPE> position = entityManager->GetValidGrainPosition();

        entityManager->AddGrain(new Grain(entityManager, position.first, position.second, 1, 1));
    }

    int total = 0;
    int i = 0;

    sf::Image screenShotImage;

	sf::Clock clock;

    bool shouldTakeSSNextFrame = true;

    while (this->ptrWindow->isOpen())
    {
        sf::Event event;
		while (this->ptrWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->ptrWindow->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			entityManager->drawAnts = !entityManager->drawAnts;
		}

		this->ptrWindow->clear();

        for (i = 0; i < 1000; i++) {
            if (total = 1'000'000) {
                entityManager->Update();
            }
            total++;

            if (total == 1 || total == 500'000 || total == 999'999) {
                entityManager->Draw();

                printf("Total: %d\n", total);

                this->ptrWindow->display();

                screenShotImage = ptrWindow->capture();

                std::ostringstream s;
                s << "frame_" << total << ".jpg";

                printf("Savez!\n");

                screenShotImage.saveToFile(s.str());
            }
        }

		entityManager->Draw();

        printf("Total: %d\n", total);

		this->ptrWindow->display();
    }
}

void Application::ProcessLoop() {

}
