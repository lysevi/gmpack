#ifndef CANIMATION_H
#define CANIMATION_H

class Animation {
private:
    int CurrentFrame;

    int FrameInc;

private:
    int FrameRate; //Milliseconds

    long OldTime;

public:
    int MaxFrames;

    bool Oscillate;

public:
    Animation();
    Animation(const Animation&orig);

    void OnAnimate();

public:
    void SetFrameRate(int Rate);

    void SetCurrentFrame(int Frame);

    int GetCurrentFrame();
};
#endif // CANIMATION_H
