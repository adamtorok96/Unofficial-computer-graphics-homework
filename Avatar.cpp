#include "Avatar.h"
#include "shadow.h"

void Avatar::init()
{
    spaceShip.read("media/TIEInterceptor.obj");
}

void Avatar::render()
{
    glPushMatrix();
    transform();
    spaceShip.render();
    glPopMatrix();
}

void Avatar::transform()
{
    float t = gameController.timeSinceInitCompleted < gameController.timeIntro ? t = 0 : t = gameController.timeSinceInitCompleted - gameController.timeIntro;

    glTranslatef(-0.47, -2.6, 2.0);

    float percent;

    if (gameController.timeGameStart < 0.0)
    {
        percent = 1.0;
    }
    else
    {
        if (gameController.timeSinceInitCompleted - gameController.timeGameStart < gameController.timeOfTransitionFromIntroEndToUserControl)
        {
            percent = 1.0 - (gameController.timeSinceInitCompleted - gameController.timeGameStart);
        }
        else
        {
            percent = 0.0;
            gameController.userControlOn = true;
        }
    }

    if (gameController.userControlOn)
    {
        glTranslatef(imageProcessor.virtualMouseDeltaX, 0, -imageProcessor.virtualMouseDeltaY);
    }

    glTranslatef((1.0 - percent) * 0.47, (1.0 - percent) * 0.0, (1.0 - percent) * -2.0);
    glRotatef(percent * fmod(t * 13, 360), 1, 0, 0);
    glRotatef(percent * fmod(t * 29, 360), 0, 0, 1);
    glTranslatef(percent * 0.5*sin(M_PI / 2.0 * std::min(t / 10.0, 1.0)), 0, 0);

    glRotatef(percent * 90, 0, 1, 0);
    glRotatef(-180, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 0.5, 0.5);
}