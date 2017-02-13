#ifndef SHADOW_IMAGESOURCE_H
#define SHADOW_IMAGESOURCE_H

#include <opencv2/opencv.hpp>

class ImageSource {

public:

    virtual bool init(int intParam = 0, const char *strParam = NULL) = 0;
    virtual bool getImage(cv::Mat &img) = 0;

};

#endif //SHADOW_IMAGESOURCE_H
