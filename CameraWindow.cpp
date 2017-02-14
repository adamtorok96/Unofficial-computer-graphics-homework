#include "CameraWindow.h"

void CameraWindow::init() {
    videoCapture.open(0);

    namedWindow(cameraWindowName, CV_WINDOW_AUTOSIZE);

    videoCapture.read(prevFrame);

    resize(prevFrame, prevFrame, Size(width, height));
    flip(prevFrame, prevFrame, 1);
}

void CameraWindow::render() {
    videoCapture.read(frame);

    resize(frame, frame, Size(width, height));
    flip(frame, frame, 1);

    Point2f actualFlow = calculateFlow();

    imshow(cameraWindowName, prevFrame);

    waitKey(1);

    prevFrame = frame;
}
// Source: http://study.marearts.com/2014/04/opencv-study-calcopticalflowfarneback.html
Point2f CameraWindow::calculateFlow() {

    Mat flowVectors, flowVectors2;
    Point2f accFlow(0, 0);

    cvtColor(prevFrame, prevFrameGray, COLOR_RGB2GRAY);
    cvtColor(frame, frameGray, COLOR_RGB2GRAY);

    calcOpticalFlowFarneback(prevFrameGray, frameGray, flowVectors, 0.5, 3, 15, 3, 5, 1.2, 0);

    threshold(flowVectors, flowVectors2, 1.0, 0, THRESH_TOZERO);
    threshold(flowVectors, flowVectors, -1.0, 0, THRESH_TOZERO_INV);

    sumFlow[sumFlowIndex] = sum(flowVectors) + sum(flowVectors2);
    sumFlow[sumFlowIndex] /= 5000.0;

    sumFlowIndex = (sumFlowIndex + 1) % memoryLength;

    for (int i = 0; i< memoryLength; i++) {
        accFlow.x += sumFlow[i][0];
        accFlow.y += sumFlow[i][1];
    }

    if (fabs(accFlow.x) < 20.0)
        accFlow.x = 0;

    if (fabs(accFlow.y) < 20.0)
        accFlow.y = 0;

    line(
            prevFrame,
            Point(prevFrame.cols / 2, prevFrame.rows / 2),
            Point((int) (prevFrame.cols / 2 + accFlow.x), (int) (prevFrame.rows / 2 + accFlow.y)),
            Scalar(0, 255, 0),
            5
    );

    const int step = 10;

    for (int i = 0; i < flowVectors.rows; i += step)
    {
        for (int j = 0; j<flowVectors.cols; j += step)
        {
            const Point2f& fxy = flowVectors.at<Point2f>(i, j);
            line(
                    prevFrame,
                    Point(j, i),
                    Point((int) (j + fxy.x), (int) (i + fxy.y)),
                    Scalar(0, 255, 0),
                    1
            );
        }
    }

    return accFlow;
}