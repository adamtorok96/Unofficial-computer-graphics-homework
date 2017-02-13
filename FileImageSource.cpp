#include "FileImageSource.h"

FileImageSource::FileImageSource()
{
    filenameFormat[0] = 0;
}

bool FileImageSource::init(int intParam, const char *strParam)
{
    firstFileNum = fileNum = intParam;
    if (strParam)
    {
        strncpy(filenameFormat, strParam, sizeof(filenameFormat));
    }

    return true;
}

bool FileImageSource::getImage(cv::Mat &img)
{
    char actualFilename[sizeof(filenameFormat)];
    sprintf(actualFilename, filenameFormat, fileNum++);
    img = cv::imread(actualFilename, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data)
    {
        if (fileNum == firstFileNum) throw actualFilename;

        fileNum = firstFileNum;
        if (!getImage(img))
        {
            throw actualFilename;
        }
        return true;
    }

    return (bool) (img.rows | img.cols);
}