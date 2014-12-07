/* 
 * File:   FPS.h
 * Author: lsv
 *
 * Created on 6 декабря 2014 г., 7:36
 */

#pragma once

#include <SDL/SDL.h>
namespace core {

    class FPS {
    public:
        static FPS FPSControl;

    private:
        int OldTime;
        int LastTime;

        float SpeedFactor;

        int NumFrames;
        int Frames;

    public:
        FPS();

        void OnLoop();

    public:
        int GetFPS();

        float GetSpeedFactor();
    };
}