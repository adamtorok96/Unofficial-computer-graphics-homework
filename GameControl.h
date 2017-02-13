#ifndef SHADOW_GAMECONTROL_H
#define SHADOW_GAMECONTROL_H

class GameControl {

    float timeOfInitCompleted;
    float timeSkip = 0.0;

public:

    bool userControlOn;
    float timeSinceInitCompleted;
    float timeGameStart;
    const float timeIntro = 27.0;
    const float timeOfTransitionFromIntroEndToUserControl = 1.0;

    GameControl();

    void captureTimeSinceInitCompleted();
    void setTimeOfInitCompleted();
    void skipIntro();



};


#endif //SHADOW_GAMECONTROL_H
