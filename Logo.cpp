#include "Logo.h"

void Logo::init() {
    imageSource.setFlags(CV_LOAD_IMAGE_UNCHANGED);
    imageSource.init(0, "media/web_hi_res_512.png");
    imageSource.getImage(image);

    flip(image, image, 0);
    resize(image, image, cv::Size(SIZE, SIZE));
}

void Logo::render() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRasterPos3f(-0.55f, 0.475, -1.f);
    glDrawPixels(SIZE, SIZE, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
}
