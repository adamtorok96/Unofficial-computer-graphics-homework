#include "CameraWindow.h"

void CameraWindow::init() {
    posCursor = Point(width / 2, height / 2);

    //videoCapture.open("http://213.16.87.163:8092/axis-cgi/mjpg/video.cgi?resolution=640x480");
    videoCapture.open(0);

    if( !videoCapture.isOpened() ) {
        printf("Failed to open\n"); return;
    }

    namedWindow(cameraWindowName, CV_WINDOW_AUTOSIZE);

    videoCapture.read(prevFrame);

    resize(prevFrame, prevFrame, Size(width, height));
    flip(prevFrame, prevFrame, 1);
}

void CameraWindow::render() {
    videoCapture.read(frame);

    resize(frame, frame, Size(width, height));
    flip(frame, frame, 1);

    flow = calculateFlow();

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
    sumFlow[sumFlowIndex] /= 5000.0;  //5000.0

    sumFlowIndex = (sumFlowIndex + 1) % memoryLength;

    for (int i = 0; i < memoryLength; i++) {
        accFlow.x += sumFlow[i][0];
        accFlow.y += sumFlow[i][1];
    }

    if (fabs(accFlow.x) < 20.0)
        accFlow.x = 0;

    if (fabs(accFlow.y) < 20.0)
        accFlow.y = 0;


    Point2f vector(accFlow.x, accFlow.y);

    line(
            prevFrame,
            Point(prevFrame.cols / 2, prevFrame.rows / 2),
            Point((int) (prevFrame.cols / 2 + accFlow.x), (int) (prevFrame.rows / 2 + accFlow.y)),
            Scalar(0, 255, 0),
            5
    );

    //norm(vector);

    //printf("vec: %f %f %d %d\n", vector.x, vector.y, posCursor.x, posCursor.y);

    vector *= 0.45;

    //if( accFlow.x != 0 )
        posCursor.x += vector.x;

    //if( accFlow.y != 0 )
        posCursor.y += vector.y;

    if( posCursor.x > width )
        posCursor.x = width;
    else if( posCursor.x < 0 )
        posCursor.x = 0;

    if( posCursor.y > height )
        posCursor.y = height;
    else if( posCursor.y < 0 )
        posCursor.y = 0;

    circle(
            prevFrame,
            posCursor,
            10,
            Scalar(0, 0, 255),
            2
    );

    static const int step = 10;

    for (int i = 0; i < flowVectors.rows; i += step) {
        for (int j = 0; j < flowVectors.cols; j += step) {
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

Point2f CameraWindow::getFlow() {
    return flow;
}

void CameraWindow::detectFace() {
/*
    std::vector<Rect> faces, faces2;

    const static Scalar colors[] =
            {
                    Scalar(255,0,0),
                    Scalar(255,128,0),
                    Scalar(255,255,0),
                    Scalar(0,255,0),
                    Scalar(0,128,255),
                    Scalar(0,255,255),
                    Scalar(0,0,255),
                    Scalar(255,0,255)
            };

    Mat smallImg;

    double fx = 1; // / scale;

    resize(prevFrameGray, smallImg, Size(), fx, fx, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    cascade.detectMultiScale( smallImg, faces,
                              1.1, 2, 0
                                      //|CASCADE_FIND_BIGGEST_OBJECT
                                      //|CASCADE_DO_ROUGH_SEARCH
                                      |CASCADE_SCALE_IMAGE,
                              Size(30, 30) );


    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        Mat smallImgROI;
        std::vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5));
            center.y = cvRound((r.y + r.height*0.5));
            radius = cvRound((r.width + r.height)*0.25);
            circle(prevFrame, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( prevFrame, cvPoint(cvRound(r.x), cvRound(r.y)),
                       cvPoint(cvRound((r.x + r.width-1)), cvRound((r.y + r.height-1))),
                       color, 3, 8, 0);
        if( nestedCascade.empty() )
            continue;
        smallImgROI = smallImg( r );
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
                                        1.1, 2, 0
                                                //|CASCADE_FIND_BIGGEST_OBJECT
                                                //|CASCADE_DO_ROUGH_SEARCH
                                                //|CASCADE_DO_CANNY_PRUNING
                                                |CASCADE_SCALE_IMAGE,
                                        Size(30, 30) );

        /*
        for ( size_t j = 0; j < nestedObjects.size(); j++ )
        {
            Rect nr = nestedObjects[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
            radius = cvRound((nr.width + nr.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }*/
  //  } 
}
