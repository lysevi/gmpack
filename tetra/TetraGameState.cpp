/* 
 * File:   TetraGameState.cpp
 * Author: lsv
 * 
 * Created on 6 декабря 2014 г., 16:57
 */

#include "TetraGameState.h"
#include <ProcessLogger.h>

TetraGameState::TetraGameState() {
    for(int i=0;i<map_height;++i)
        for(int j=0;j<map_width;++j)
            m_map[i][j]=0;
}

void TetraGameState::OnActivate(){

}

void TetraGameState::OnDeactivate(){

}

void TetraGameState::OnLoop(){

}

void TetraGameState::OnRender(SDL_Surface* Surf_Display){
    SDL_Rect dstrect;
    dstrect.h = 480;
    dstrect.w = 640;
    dstrect.x = 0;
    dstrect.y = 0;
    SDL_FillRect(Surf_Display,&dstrect,0);
}
