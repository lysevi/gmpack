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
    writeOnMap();
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
        if(isBottom()){
            m_curtype=getRandomBlockType();
            blck_x=0;
        }
        else{
            blck_x++;
        }
        writeOnMap();
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

block_type TetraGameState::getRandomBlockType()const {
    auto rnd_result = (block_type) ((rand() % (block_type::End - 1)) + 1);
    assert(rnd_result != 0);
    return rnd_result;
}

void TetraGameState::writeOnMap() {
    logger << "x=" << blck_x << " y=" << blck_y << " type=" << m_curtype<<endl;
    if(isBottom()){
        return;
    }
    if (m_curtype == block_type::I) {
        m_map[blck_x+1][blck_y] = 1;
        m_map[blck_x+1][blck_y + 1] = 1;
        m_map[blck_x+1][blck_y + 2] = 1;
        m_map[blck_x+1][blck_y + 3] = 1;
    }

    if (m_curtype == block_type::J) {
        m_map[blck_x][blck_y] = 1;
        m_map[blck_x + 1][blck_y] = 1;
        m_map[blck_x + 1][blck_y + 1] = 1;
        m_map[blck_x + 1][blck_y + 2] = 1;
    }

    if (m_curtype == block_type::L) {
        m_map[blck_x][blck_y] = 1;
        m_map[blck_x + 1][blck_y] = 1;
        m_map[blck_x + 1][blck_y + 1] = 1;
        m_map[blck_x + 1][blck_y + 2] = 1;
    }

    if (m_curtype == block_type::O) {
        m_map[blck_x][blck_y] = 1;
        m_map[blck_x][blck_y + 1] = 1;
        m_map[blck_x + 1][blck_y] = 1;
        m_map[blck_x + 1][blck_y + 1] = 1;
    }

    if (m_curtype == block_type::S) {
        m_map[blck_x][blck_y] = 1;
        m_map[blck_x][blck_y + 1] = 1;
        m_map[blck_x + 1][blck_y] = 1;
        m_map[blck_x + 1][blck_y - 1] = 1;
    }

    if (m_curtype == block_type::T) {
        m_map[blck_x][blck_y] = 1;
        m_map[blck_x + 1][blck_y] = 1;
        m_map[blck_x + 1][blck_y + 1] = 1;
        m_map[blck_x + 1][blck_y - 1] = 1;
    }

    if (m_curtype == block_type::Z) {
        m_map[blck_x][blck_y] = 1;
        m_map[blck_x][blck_y - 1] = 1;
        m_map[blck_x + 1][blck_y] = 1;
        m_map[blck_x + 1][blck_y + 1] = 1;
    }
}


bool TetraGameState::isBottom(){
    return  blck_x==map_height-1;

}