//
// Created by d on 18/03/19.
//

#ifndef ANTS_ANT_HPP
#define ANTS_ANT_HPP

#include "AntManager.hpp"


class Ant {
public:
    unsigned int posX, posY;

    bool dead;

    AntManager      *ptrAntManager;

    Ant(AntManager*, unsigned int, unsigned int);


    void Update();
    void Draw();

};


#endif //ANTS_ANT_HPP
