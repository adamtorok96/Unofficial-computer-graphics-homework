#ifndef SHADOW_WEBCAMERAWINDOW_H
#define SHADOW_WEBCAMERAWINDOW_H

#include <opencv2/opencv.hpp>

#include "GameElement.h"

using namespace cv;

class CameraWindow : public GameElement {

    static const int width = 320;
    static const int height = 240;

    const char *cameraWindowName = "Camera";

    VideoCapture videoCapture;
    Mat frame;

public:
    void init();
    void render();
};


#endif //SHADOW_WEBCAMERAWINDOW_H
