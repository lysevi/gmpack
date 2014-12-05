/* 
 * File:   TicTacGameState.cpp
 * Author: lsv
 * 
 * Created on 5 декабря 2014 г., 21:11
 */

#include "TicTacGameState.h"
#include "ProcessLogger.h"

TicTacGameState::TicTacGameState() {
}

void TicTacGameState::OnActivate() {
}

void TicTacGameState::OnDeactivate() {
}

void TicTacGameState::OnLoop() {

}

void TicTacGameState::OnRender(SDL_Surface* Surf_Display) {
    logger << "TicTacGameState::OnRender" << endl;
    SDL_Rect dstrect;
    dstrect.h = 480;
    dstrect.w = 640;
    dstrect.x = 0;
    dstrect.y = 0;

    SDL_FillRect(Surf_Display, &dstrect, 0);
}
