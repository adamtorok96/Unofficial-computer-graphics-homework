#include "GameControl.h"
#include <GL/freeglut.h>

GameControl::GameControl()
        : userControlOn(false)
        , timeOfInitCompleted(0.0)
        , timeSinceInitCompleted(0.0)
        , timeGameStart((float) -1.0)
{}

void GameControl::captureTimeSinceInitCompleted()
{
    timeSinceInitCompleted = (glutGet(GLUT_ELAPSED_TIME) / 1000.0 - timeOfInitCompleted + timeSkip);
}

void GameControl::setTimeOfInitCompleted()
{
    timeOfInitCompleted = (glutGet(GLUT_ELAPSED_TIME) / 1000.0);
}

void GameControl::skipIntro()
{
    timeSkip = timeIntro;
}