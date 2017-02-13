#include "CrawlerScroll.h"

void CrawlerScroll::init()
{
    texBigscroll = createTextureFromFile("media/iitcg.png");

    for (int h = 0; h < numTrollPhases; h++)
    {
        char fname[32];
        sprintf(fname, "media/source%d.png", h);
        texTroll[h] = createTextureFromFile(fname);
    }

    arrowTrollStartTimeSec = -5.0;
    trollPhase = 0;
}

void CrawlerScroll::render()
{
    const float crawlerLeftX = -1.5, crawlerTopY =  0.0, crawlerRightX =  1.5, crawlerBottomY = -5.0;
    const float trollLeftX   = -1.33, trollTopY  = -1.685, trollRightX = -0.51, trollBottomY  = -2.28;
    const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};

    glDisable(GL_DEPTH_TEST);
    glNormal3f(0, 0, 1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texBigscroll);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(crawlerLeftX, crawlerTopY);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(crawlerRightX, crawlerTopY);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(crawlerRightX, crawlerBottomY);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(crawlerLeftX, crawlerBottomY);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texTroll[trollPhase]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.005, 0.995);
    glVertex2f(trollLeftX, trollTopY);
    glTexCoord2f(0.995, 0.995);
    glVertex2f(trollRightX, trollTopY);
    glTexCoord2f(0.995, 0.005);
    glVertex2f(trollRightX, trollBottomY);
    glTexCoord2f(0.005, 0.005);
    glVertex2f(trollLeftX, trollBottomY);
    glEnd();

    renderArrowAndCalculateTrollPhase(gameController.timeSinceInitCompleted);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

void CrawlerScroll::redArrow(float ratio)
{
    const float vertices[][3] =
            {
                    { 0.00, -1.5 + 0.00, 0.00 },
                    { 0.00, -1.5 + 0.045, 0.00 },
                    { 0.38, -1.5 + 0.045, 0.00 },
                    { 0.38, -1.5 + 0.00, 0.00 },
                    { -1.25, -1.5 + 0.00, 0.00 },
                    { -1.25, -1.5 - 0.045, 0.00 },
                    { -1.60, -1.5 - 0.045, 0.00 },
                    { -1.60, -1.5 + 0.00, 0.00 },
                    { -1.25, -1.5 + 0.00, 0.00 },
                    { -1.25, -1.5 + 0.80, 0.00 },
                    { -1.70, -1.5 + 0.80, 0.00 },
            };
    const int numVertices = sizeof(vertices) / sizeof(float[3]) - 1;

    GLfloat apex[3];
    int i;

    if (ratio <= 0.0) return;
    if (ratio > 1.0) ratio = 1.0;

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(1.5);
    glPushMatrix();
    glTranslatef(1.08, -1.265, 0);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i< numVertices; i++)
    {
        glVertex3fv(vertices[i]);
        float upscale = ratio * (numVertices);

        if ((int)upscale <= i)
        {
            float fraction = upscale - i;
            apex[0] = vertices[i][0] + (vertices[i + 1][0] - vertices[i][0])*fraction;
            apex[1] = vertices[i][1] + (vertices[i + 1][1] - vertices[i][1])*fraction;
            apex[2] = vertices[i][2] + (vertices[i + 1][2] - vertices[i][2])*fraction;
            glVertex3fv(apex);
            break;
        }
    }
    glEnd();
    glTranslatef(apex[0], apex[1], apex[2]);
    glRotatef(180.0*atan2((vertices[i + 1][1] - vertices[i][1]), (vertices[i + 1][0] - vertices[i][0])) / M_PI, 0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.03, 0.01, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(-0.03, -0.01, 0);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void CrawlerScroll::renderArrowAndCalculateTrollPhase(float actualTime)
{
    trollPhase = 0;

    if (actualTime < arrowTrollStartTimeSec) return;
    if (actualTime > arrowTrollStartTimeSec + arrowTime + trollTime) return;
    if (actualTime <= arrowTrollStartTimeSec + arrowTime) redArrow((actualTime - arrowTrollStartTimeSec) / arrowTime);
    else trollPhase = 23.0 * (0.5 - fabs(0.5 - (actualTime - (arrowTrollStartTimeSec + arrowTime)) / trollTime));
}
