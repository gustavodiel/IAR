//
// Created by d on 18/03/19.
//

#ifndef ANTS_APPLICATION_H
#define ANTS_APPLICATION_H

#include <SFML/Graphics.hpp>

class Application {
public:

    unsigned int windowX, windowY;

    Application(unsigned int _x, unsigned int _y);

    void Start();

private:

    sf::RenderWindow        *ptrWindow;

    void ProcessLoop();

};


#endif //ANTS_APPLICATION_H
