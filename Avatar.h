#ifndef SHADOW_AVATAR_H
#define SHADOW_AVATAR_H

#include <algorithm>

#include "utility2d3d.hpp"

#include "ImageProcessor.h"
#include "GameElement.h"
#include "GameControl.h"
#include "Mesh.h"


class Avatar : public GameElement {

    Mesh spaceShip;

    void transform();

public:

    void init();
    void render();

};


#endif //SHADOW_AVATAR_H
