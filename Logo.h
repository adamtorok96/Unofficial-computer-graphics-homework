#ifndef SHADOW_LOGO_H
#define SHADOW_LOGO_H

#include <GL/freeglut.h>

#include <opencv2/opencv.hpp>

#include "GameElement.h"
#include "FileImageSource.h"

#ifndef CV_LOAD_IMAGE_UNCHANGED
#define CV_LOAD_IMAGE_UNCHANGED -1
#endif

class Logo : public GameElement {

    static const int SIZE = 64;

    FileImageSource imageSource;
    cv::Mat image;

public:
    void init();
    void render();
};


#endif //SHADOW_LOGO_H
