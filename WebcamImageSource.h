#ifndef SHADOW_WEBCAMIMAGESOURCE_H
#define SHADOW_WEBCAMIMAGESOURCE_H


#include "ImageSource.h"

class WebcamImageSource : public virtual ImageSource {

    bool init(int intParam = 0, const char *strParam = NULL);
    bool getImage(cv::Mat &img);

};


#endif //SHADOW_WEBCAMIMAGESOURCE_H
