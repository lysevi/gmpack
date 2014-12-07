/* 
 * File:   TetraGameState.h
 * Author: lsv
 *
 * Created on 6 декабря 2014 г., 16:57
 */

#pragma once

#include <AppState.h>
#include <Coord.h>
#include <list>

const int map_width=10;
const int map_height=20;
const int block_width=30;

enum block_type{
    I=1,
    J,
    L,
    O,
    S,
    T,
    Z,
    End
};

typedef std::list<core::Coord> CoordList;

class TetraGameState: public AppState {
    char m_map[map_height][map_width];
    block_type m_curtype;
    int blck_line, blck_column, shift;
    int MoveTime;
    int CurTime;
public:
    TetraGameState();
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
private:
    block_type getRandomBlockType()const;
    void writeOnMap(const CoordList& coords,int value);
    CoordList getBlockCoord(int line,int column)const;
    bool isBottom(const CoordList&coords);
};

