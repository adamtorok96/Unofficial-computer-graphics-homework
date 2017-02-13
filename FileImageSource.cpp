#include "FileImageSource.h"

FileImageSource::FileImageSource()
{
    flags = CV_LOAD_IMAGE_GRAYSCALE;
    filenameFormat[0] = 0;
}

bool FileImageSource::init(int intParam, const char *strParam)
{
    firstFileNum = fileNum = intParam;

    if (strParam) {
        strncpy(filenameFormat, strParam, sizeof(filenameFormat));
    }

    return true;
}

bool FileImageSource::getImage(cv::Mat &img)
{
    char actualFilename[sizeof(filenameFormat)];
    sprintf(actualFilename, filenameFormat, fileNum++);

    img = cv::imread(actualFilename, flags);

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

void FileImageSource::setFlags(int flags) {
    this->flags = flags;
}
