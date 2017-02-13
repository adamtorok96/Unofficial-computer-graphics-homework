#include "Logo.h"
#include "utility2d3d.hpp"

void Logo::init() {
    imageSource.init(0, "media/web_hi_res_512.png");
    imageSource.getImage(image);

    flip(image, image, 0);
    resize(image, image, cv::Size(SIZE, SIZE));
}

void Logo::render() {
    //glPixelZoom(0.5f, 0.5f);
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //glLoadIdentity();
    glRasterPos3f(0, 0, -1.f);
    glDrawPixels(SIZE, SIZE, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
   // glFlush();
}
