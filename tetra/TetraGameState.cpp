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
#include <algorithm>

TetraGameState::TetraGameState() {
    srand(time(0));
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_width; ++j) {
            m_map[i][j] = 0;
        }
    }
    CurTime = 0;
    MoveTime = 500;
    blck_line = 0;
    blck_column = static_cast<int> (map_width / 2);
    m_curtype = getRandomBlockType();
    writeOnMap(getBlockCoord(blck_line,blck_column),1);
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
        
        writeOnMap(getBlockCoord(blck_line,blck_column),0);

        if(shift!=0){
            blck_column+=shift;
            shift=0;
        }

        auto next_coords=getBlockCoord(blck_line+1,blck_column);
        if(isBottom(next_coords)){
            writeOnMap(getBlockCoord(blck_line,blck_column),1);
            m_curtype=getRandomBlockType();
            blck_line=0;
            next_coords=getBlockCoord(blck_line,blck_column);
        }else{
            blck_line++;
        }
        
        writeOnMap(next_coords,1);
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

void TetraGameState::writeOnMap(const CoordList& coords,int value) {
    //logger << "x=" << blck_x << " y=" << blck_y << " type=" << m_curtype<<endl;
    for(auto c:coords){
        m_map[c.x][c.y]=value;
    }
    
}

CoordList TetraGameState::getBlockCoord(int line,int column)const{
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

bool TetraGameState::isBottom(const CoordList&coords){
    return std::any_of(coords.cbegin(), coords.cend(),[&m_map](const core::Coord c){
        return (c.x==map_height)||(m_map[c.x][c.y]!=0);
    });
}