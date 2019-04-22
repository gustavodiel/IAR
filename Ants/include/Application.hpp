//
// Created by d on 18/03/19.
//

#ifndef ANTS_APPLICATION_H
#define ANTS_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "Defines.hpp"

class Application {
public:

    MAP_TYPE windowX, windowY;

    Application(MAP_TYPE _x, MAP_TYPE _y);

    void Start();

private:

    sf::RenderWindow        *ptrWindow;

    void ProcessLoop();

};

void* thread_job(void*);


#endif //ANTS_APPLICATION_H
