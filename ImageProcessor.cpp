#include "ImageProcessor.h"


ImageProcessor::ImageProcessor() : auxImage(180, 320, CV_8UC1) {}

void ImageProcessor::init()
{
    cv::namedWindow(ImageProcessWindowName, CV_WINDOW_AUTOSIZE);
    renderString("Loading, please waiit...");
    imgSource = new FileImageSource();
    imgSource->init(20, "media/img%05d.png");
}

void ImageProcessor::render()
{
    imgSource->getImage(captured);
    if (!prevCaptured.data) prevCaptured = captured;
    cv::Point2f actualFlow = calculateFlow();
//		virtualMouseDeltaX += actualFlow.x * 0.002;
//		virtualMouseDeltaY += actualFlow.y * 0.002;

    cv::imshow(ImageProcessWindowName, prevCaptured);
    cv::waitKey(1);
    prevCaptured = captured;
}

void ImageProcessor::renderString(const char *message)
{
    auxImage.setTo(0); // imageProcessor.
    drawTextToCenter(auxImage, message);
    cv::imshow(ImageProcessWindowName, auxImage);
    cv::waitKey(1);
}

cv::Point2f ImageProcessor::calculateFlow()
{
    cv::Mat flowVectors, flowVectors2;
    cv::Point2f accFlow(0, 0);

    cv::calcOpticalFlowFarneback(prevCaptured, captured, flowVectors, 0.5, 3, 15, 3, 5, 1.2, 0);
    cv::threshold(flowVectors, flowVectors2, 1.0, 0, cv::THRESH_TOZERO);
    cv::threshold(flowVectors, flowVectors, -1.0, 0, cv::THRESH_TOZERO_INV);

    sumFlow[sumFlowIndex] = cv::sum(flowVectors) + cv::sum(flowVectors2);
    sumFlow[sumFlowIndex] /= 5000.0;
    sumFlowIndex = (sumFlowIndex + 1) % memoryLength;
    for (int i = 0; i<memoryLength; i++)
    {
        accFlow.x += sumFlow[i][0];
        accFlow.y += sumFlow[i][1];
    }

    if (fabs(accFlow.x) < 20.0) accFlow.x = 0;
    if (fabs(accFlow.y) < 20.0) accFlow.y = 0;

    cv::line(prevCaptured, cv::Point(prevCaptured.cols / 2, prevCaptured.rows / 2), cv::Point(prevCaptured.cols / 2 + accFlow.x, prevCaptured.rows / 2 + accFlow.y), cv::Scalar(255), 5);

    const int step = 10;
    for (int i = 0; i<flowVectors.rows; i += step)
    {
        for (int j = 0; j<flowVectors.cols; j += step)
        {
            const cv::Point2f& fxy = flowVectors.at<cv::Point2f>(i, j);
            cv::line(prevCaptured, cv::Point(j, i), cv::Point(j + fxy.x, i + fxy.y), cv::Scalar(255), 1);
        }
    }

    return accFlow;
}