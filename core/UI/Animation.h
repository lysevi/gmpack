#pragma once

namespace core {

    class Animation {
    private:
        int CurrentFrame;

        int FrameInc;

    private:
        Uint32 FrameRate; //Milliseconds

        Uint32 OldTime;

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
}
