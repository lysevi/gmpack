/* 
 * File:   TetraGameState.cpp
 * Author: lsv
 * 
 * Created on 6 декабря 2014 г., 16:57
 */

#include "TetraGameState.h"
#include "Surface.h"
#include <ProcessLogger.h>
#include <cstdlib>
#include <cassert>

TetraGameState::TetraGameState() {
    srand(time(0));
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_width; ++j) {
            m_map[i][j] = 0;
        }
    }
    CurTime = 0;
    MoveTime = 500;
    blck_x = 0;
    blck_y = static_cast<int> (map_width / 2);
    m_curtype = getRandomBlockType();
    writeOnMap(getBlockCoord(blck_x,blck_y),1);
}

void TetraGameState::OnActivate() {

}

void TetraGameState::OnDeactivate() {

}

void TetraGameState::OnLoop() {
    if (CurTime == 0) {
        CurTime = SDL_GetTicks();
    } else if (MoveTime + CurTime < SDL_GetTicks()) {
        CurTime = SDL_GetTicks();
        writeOnMap(getBlockCoord(blck_x,blck_y),0);
        if(isBottom()){
            m_curtype=getRandomBlockType();
            blck_x=0;
        }
        else{
            blck_x++;
        }
        if(shift!=0){
            blck_y+=shift;
            shift=0;
        }
        writeOnMap(getBlockCoord(blck_x,blck_y),1);
    }
}

void TetraGameState::OnRender(SDL_Surface* Surf_Display) {
    Surface::ClearSurface(Surf_Display, 0);

    SDL_Rect dstrect;
    dstrect.h = block_width*map_height;
    dstrect.w = block_width*map_width;
    dstrect.x = 0;
    dstrect.y = 0;
    auto bg_colour = SDL_MapRGB(Surf_Display->format, 0xff, 0xff, 0x99);

    SDL_FillRect(Surf_Display, &dstrect, bg_colour);

    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_width; ++j) {
            if (m_map[i][j] == 0)
                continue;
            auto x = j*block_width;
            auto y = i*block_width;

            SDL_Rect block_rect;
            block_rect.h = block_width;
            block_rect.w = block_width;
            block_rect.x = x;
            block_rect.y = y;

            auto blck_clr = SDL_MapRGB(Surf_Display->format, 0, 0, 0);
            SDL_FillRect(Surf_Display, &block_rect, blck_clr);
        }
    }
}

void TetraGameState::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
    
    if(sym == SDLKey::SDLK_LEFT){
        shift=-1;
    }
    
    if(sym == SDLKey::SDLK_RIGHT){
        shift= 1;
    }
}

block_type TetraGameState::getRandomBlockType()const {
    auto rnd_result = (block_type) ((rand() % (block_type::End - 1)) + 1);
    assert(rnd_result != 0);
    return rnd_result;
}

void TetraGameState::writeOnMap(std::list<core::Coord> coords,int value) {
    //logger << "x=" << blck_x << " y=" << blck_y << " type=" << m_curtype<<endl;
    if(isBottom()){
        return;
    }
    for(auto c:coords){
        m_map[c.x][c.y]=value;
    }
    
}

std::list<core::Coord> TetraGameState::getBlockCoord(int line,int column)const{
    std::list<core::Coord> result;
    if (m_curtype == block_type::I) {
        result.push_back({line+1,column});
        result.push_back({line+1,column + 1});
        result.push_back({line+1,column + 2});
        result.push_back({line+1,column + 3});
    }

    if (m_curtype == block_type::J) {
        result.push_back({line,column});
        result.push_back({line + 1,column});
        result.push_back({line + 1,column + 1});
        result.push_back({line + 1,column + 2});
    }

    if (m_curtype == block_type::L) {
        result.push_back({line,column});
        result.push_back({line + 1,column});
        result.push_back({line + 1,column + 1});
        result.push_back({line + 1,column + 2});
    }

    if (m_curtype == block_type::O) {
        result.push_back({line,column});
        result.push_back({line,column + 1});
        result.push_back({line + 1,column});
        result.push_back({line + 1,column + 1});
    }

    if (m_curtype == block_type::S) {
        result.push_back({line,column});
        result.push_back({line,column + 1});
        result.push_back({line + 1,column});
        result.push_back({line + 1,column - 1});
    }

    if (m_curtype == block_type::T) {
        result.push_back({line,column});
        result.push_back({line + 1,column});
        result.push_back({line + 1,column + 1});
        result.push_back({line + 1,column - 1});
    }

    if (m_curtype == block_type::Z) {
        result.push_back({line,column});
        result.push_back({line,column - 1});
        result.push_back({line + 1,column});
        result.push_back({line + 1,column + 1});
    }
    return result;
}

bool TetraGameState::isBottom(){
    return  blck_x==map_height-1;

}