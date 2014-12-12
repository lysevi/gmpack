/* 
 * File:   AppStateIntro.h
 * Author: lsv
 *
 * Created on 5 декабря 2014 г., 20:20
 */

#pragma once

#include "AppState.h"
#include "../UI/Surface.h"
namespace core {

    class AppStateIntro : public AppState {
    private:
        SDL_Surface* Surf_Logo;
        int StartTime;
        std::string m_FileName;
        uint m_time;
    public:
        AppStateIntro(const std::string FileName, uint _time = 3000);
        void OnActivate();
        void OnDeactivate();
        void OnLoop();
        void OnRender();
    };
}