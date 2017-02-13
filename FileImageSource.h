#ifndef SHADOW_FILEIMAGESOURCE_H
#define SHADOW_FILEIMAGESOURCE_H


#include "ImageSource.h"

class FileImageSource : public virtual ImageSource {

    char filenameFormat[512];
    int  fileNum;
    int  firstFileNum;

public:
    FileImageSource();

    bool init(int intParam, const char *strParam);
    bool getImage(cv::Mat &img);
};


#endif //SHADOW_FILEIMAGESOURCE_H
