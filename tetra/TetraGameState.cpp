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
#include <list>

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
    rotated = false;
    m_curtype =  getRandomBlockType();
    writeOnMap(getBlockCoord(blck_line, blck_column), 1);
}

void TetraGameState::OnActivate() {

}

void TetraGameState::OnDeactivate() {

}

void TetraGameState::OnLoop() {
    logger<<"score: "<<scores<<endl;
    if (CurTime == 0) {
        CurTime = SDL_GetTicks();
    } else if (MoveTime + CurTime < SDL_GetTicks()) {
        CurTime = SDL_GetTicks();

        writeOnMap(prev_coords, 0);

        if (shift != 0) {
            if (canMove(shift)) {
                blck_column += shift;
            }
            shift = 0;
        }

        auto next_coords = getBlockCoord(blck_line + 1, blck_column);
        if (isBottom(next_coords)) {
            writeOnMap(getBlockCoord(blck_line, blck_column), 1);
            m_curtype = getRandomBlockType();
            blck_line = 0;
            blck_column = static_cast<int> (map_width / 2);
            next_coords = getBlockCoord(blck_line, blck_column);
            moveDownIfFull();
        } else {
            blck_line++;
        }

        writeOnMap(next_coords, 1);
    }
}

void TetraGameState::OnRender(SDL_Surface* Surf_Display) {
    core::Surface::ClearSurface(Surf_Display, 0);

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

            drawBlock(x, y, Surf_Display);
        }
    }
}

void TetraGameState::drawBlock(int x, int y, SDL_Surface*surface) {
    static auto blck_brdr = SDL_MapRGB(surface->format, 0, 0, 100);
    static auto blck_clr = SDL_MapRGB(surface->format, 116, 64, 79);

    // border
    SDL_Rect block_rect;
    block_rect.h = block_width;
    block_rect.w = block_width;
    block_rect.x = x;
    block_rect.y = y;
    SDL_FillRect(surface, &block_rect, blck_brdr);

    //background
    block_rect.h = block_width - 2;
    block_rect.w = block_width - 2;
    block_rect.x = x + 1;
    block_rect.y = y + 1;
    SDL_FillRect(surface, &block_rect, blck_clr);
};

void TetraGameState::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    if (sym == SDLKey::SDLK_ESCAPE) {
        exit(0);
    }
    if (sym == SDLKey::SDLK_UP) {
        rotated = !rotated;
    }

    if (sym == SDLKey::SDLK_LEFT) {
        shift = -1;
    }

    if (sym == SDLKey::SDLK_RIGHT) {
        shift = 1;
    }
}

block_type TetraGameState::getRandomBlockType()const {
    auto rnd_result = (block_type) ((rand() % (block_type::End - 1)) + 1);
    assert(rnd_result != 0);
    return rnd_result;
}

void TetraGameState::writeOnMap(const CoordList& coords, int value) {
    prev_coords = coords;
    for (auto c:coords) {
        m_map[c.x][c.y] = value;
    }

}

CoordList TetraGameState::getBlockCoord(int line, int column)const {
    std::list<core::Coord> result;
    if (m_curtype == block_type::I) {
        if (!rotated) {
            result.push_back({line + 1, column});
            result.push_back({line + 1, column + 1});
            result.push_back({line + 1, column + 2});
            result.push_back({line + 1, column + 3});
        } else {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 2, column});
            result.push_back({line + 3, column});
        }
    }

    if (m_curtype == block_type::J) {
        if (!rotated) {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column + 1});
            result.push_back({line + 1, column + 2});
        } else {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 2, column});
            result.push_back({line + 2, column - 1});
        }
    }

    if (m_curtype == block_type::L) {
        if (!rotated) {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column - 1});
            result.push_back({line + 1, column - 2});
        } else {
            result.push_back({line, column - 1});
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 2, column});
        }
    }

    if (m_curtype == block_type::O) {
        result.push_back({line, column});
        result.push_back({line, column + 1});
        result.push_back({line + 1, column});
        result.push_back({line + 1, column + 1});
    }

    if (m_curtype == block_type::S) {
        if (!rotated) {
            result.push_back({line, column});
            result.push_back({line, column + 1});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column - 1});
        } else {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column + 1});
            result.push_back({line + 2, column + 1});
        }
    }

    if (m_curtype == block_type::T) {
        if (!rotated) {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column + 1});
            result.push_back({line + 1, column - 1});
        } else {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 2, column});
            result.push_back({line + 1, column - 1});
        }
    }

    if (m_curtype == block_type::Z) {
        if (!rotated) {
            result.push_back({line, column});
            result.push_back({line, column - 1});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column + 1});
        } else {
            result.push_back({line, column});
            result.push_back({line + 1, column});
            result.push_back({line + 1, column - 1});
            result.push_back({line + 2, column - 1});
        }
    }
    return result;
}

bool TetraGameState::isBottom(const CoordList&coords) {
    return std::any_of(coords.cbegin(), coords.cend(), [&m_map](const core::Coord c) {
        return (c.x == map_height) || (m_map[c.x][c.y] != 0);
    });
}

void TetraGameState::moveDownIfFull(){
    std::list<int> line2clean;
    for(int i=0;i<map_height;++i){
        bool removeCurent=true;
        for(int j=0;j<map_width;++j){
            if(m_map[i][j]==0){
                removeCurent=false;
                break;
            }
        }
        if(removeCurent){
            line2clean.push_back(i);
        }
    }
    scores+=line2clean.size();
    // сдвигаем всё что выше
    line2clean.sort();
    for(auto lineNum:line2clean){
        for(int j=0;j<map_width;++j)
            m_map[lineNum][j]=0;
        for(int i=lineNum;i>1;i--){
            for(int j=0;j<map_width;++j)
                m_map[i][j]=m_map[i-1][j];
        }
    }   
}

bool TetraGameState::canMove(int _shift) {
    auto coords_if_can_move = getBlockCoord(blck_line, blck_column + _shift);
    bool result = std::all_of(
            coords_if_can_move.cbegin(),
            coords_if_can_move.cend(),
            [&m_map, _shift](const core::Coord & c) {
                // уперлисб слева
                if ((_shift < 0)&&((m_map[c.x][c.y] != 0) || (c.y < 0)))
                    return false;
                // уперлись справа
                if ((_shift > 0)&&((m_map[c.x][c.y] != 0) || (c.y == map_width)))
                    return false;

                return true;
            });
    return result;
}