#ifndef SHADOW_WEBCAMERAWINDOW_H
#define SHADOW_WEBCAMERAWINDOW_H

#include <opencv2/opencv.hpp>

#include "GameElement.h"

using namespace cv;

class CameraWindow : public GameElement {

    static const int width  = 320;
    static const int height = 240;

    static const int memoryLength = 5;

    const char *cameraWindowName = "Camera";

    Scalar sumFlow[memoryLength];
    int sumFlowIndex = 0;

    VideoCapture videoCapture;

    Mat
            frame,
            frameGray,
            prevFrame,
            prevFrameGray;

    Point posCursor;

    Point2f calculateFlow();

public:
    void init();
    void render();
};


#endif //SHADOW_WEBCAMERAWINDOW_H
