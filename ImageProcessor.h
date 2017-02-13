#ifndef SHADOW_IMAGEPROCESSOR_H
#define SHADOW_IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include "utility2d3d.hpp"
#include "GameElement.h"
#include "ImageSource.h"
#include "FileImageSource.h"

class ImageProcessor : public GameElement {

    const char *ImageProcessWindowName = "ImageProcess";
    static const int memoryLength = 3;
    cv::Scalar sumFlow[memoryLength];
    int sumFlowIndex = 0;

    cv::Point2f calculateFlow();

public:

    float virtualMouseDeltaX = 0.0f, virtualMouseDeltaY = 0.0f;
    cv::Mat captured, prevCaptured, auxImage;
    ImageSource *imgSource;

    ImageProcessor();

    void init();
    void render();
    void renderString(const char *message);

} ;


#endif //SHADOW_IMAGEPROCESSOR_H
