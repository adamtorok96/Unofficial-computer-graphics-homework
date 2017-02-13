#include "CameraWindow.h"

void CameraWindow::init() {
    videoCapture.open(0);

    namedWindow(cameraWindowName, CV_WINDOW_AUTOSIZE);
}

void CameraWindow::render() {
    videoCapture.read(frame);
    resize(frame, frame, Size(width, height));

    imshow(cameraWindowName, frame);
    waitKey(1);
}
