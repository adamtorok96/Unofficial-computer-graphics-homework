#ifndef SHADOW_AVATAR_H
#define SHADOW_AVATAR_H


#include "GameElement.h"
#include "Mesh.h"
#include "GameControl.h"
#include "ImageProcessor.h"


class Avatar : public GameElement {

    GameControl *gameController;
    ImageProcessor *imageProcessor;

    Mesh spaceShip;

    void transform();

public:

    Avatar(GameControl *gameControl, ImageProcessor *imgProcessor);

    void init();
    void render();

};


#endif //SHADOW_AVATAR_H
