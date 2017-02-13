#ifndef SHADOW_LOGO_H
#define SHADOW_LOGO_H

#include <GL/freeglut.h>

#include <opencv2/opencv.hpp>

#include "GameElement.h"
#include "FileImageSource.h"

class Logo : public GameElement {

    static const int SIZE = 64;

    FileImageSource imageSource;
    cv::Mat image;
    //GLuint image;

public:
    void init();
    void render();
};


#endif //SHADOW_LOGO_H
