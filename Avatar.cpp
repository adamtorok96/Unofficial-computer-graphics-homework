#include "Avatar.h"

void Avatar::init() {
    spaceShip.read("media/TIEInterceptor.obj");
}

void Avatar::render() {
    glPushMatrix();

    transform();
    spaceShip.render();

    glPopMatrix();
}

void Avatar::transform() {
    glTranslatef(position.x, 1.0f, -position.y);

    //glTranslatef(0.f, 1.0f, 0.0f);
    //glRotatef(percent * fmod(t * 13, 360), 1, 0, 0);
    //glRotatef(percent * fmod(t * 29, 360), 0, 0, 1);
    //glTranslatef(percent * 0.5*sin(M_PI / 2.0 * std::min(t / 10.0, 1.0)), 0, 0);

    //glRotatef(0, 0, 1, 0);
    glRotatef(-180, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(0.35f, 0.35f, 0.35f);

    /*
    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(position.x, 0, -position.y - 2);
    glVertex3f(position.x, 0, -position.y + 30);
    glEnd();
     */
}

Point2f& Avatar::getPosition() {
    return position;
}

