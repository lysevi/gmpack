/* 
 * File:   AppState.h
 * Author: lsv
 *
 * Created on 5 декабря 2014 г., 20:19
 */

#pragma once

#include "Event.h"

class AppState : public Event {
public:
    AppState();
public:
    virtual void OnActivate() = 0;
    virtual void OnDeactivate() = 0;
    virtual void OnLoop() = 0;
    virtual void OnRender(SDL_Surface* Surf_Display) = 0;
};

