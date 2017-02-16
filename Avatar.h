#ifndef SHADOW_AVATAR_H
#define SHADOW_AVATAR_H

#include <opencv2/opencv.hpp>

#include "GameElement.h"
#include "Mesh.h"

using namespace cv;

class Avatar : public GameElement {

    Mesh spaceShip;
    Point2f position;

    bool fire;

    void transform();

public:

    void init();
    void render();

    Point2f& getPosition();
};


#endif //SHADOW_AVATAR_H
