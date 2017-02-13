#ifndef SHADOW_CRAWLERSCROLL_H
#define SHADOW_CRAWLERSCROLL_H

#include <GL/freeglut.h>

#include "GameElement.h"
#include "GameControl.h"

class CrawlerScroll : public GameElement {

    GameControl *gameController;

    int trollPhase;
    static const int numTrollPhases = 12;
    GLuint texBigscroll, texTroll[numTrollPhases];

    const float arrowTime=3.0;
    const float trollTime=1.5;

    void redArrow(float ratio);
    void renderArrowAndCalculateTrollPhase(float actualTime);

public:
    float arrowTrollStartTimeSec;

    CrawlerScroll(GameControl *gameControl);

    void init();
    void render();

};


#endif //SHADOW_CRAWLERSCROLL_H
