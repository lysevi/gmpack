/* 
 * File:   TDGame.h
 * Author: lsv
 *
 * Created on 10 декабря 2014 г., 21:59
 */

#pragma once
#include <AppState.h>
class TDGame: public core::AppState  {
public:
    TDGame();
    virtual ~TDGame();

    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
private:

};

