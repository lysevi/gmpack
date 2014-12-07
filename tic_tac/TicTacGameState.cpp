/* 
 * File:   TicTacGameState.cpp
 * Author: lsv
 * 
 * Created on 5 декабря 2014 г., 21:11
 */

#include "TicTacGameState.h"
#include "ProcessLogger.h"
#include "Surface.h"
#include <Coord.h>
#include <vector>
#include <cstdlib>

TicTacGameState::TicTacGameState() {
    std::srand(time(0));
}

void TicTacGameState::OnActivate() {
    m_bg = core::Surface::OnLoad("tic_tac/img/bg.bmp");
    m_x = core::Surface::OnLoad("tic_tac/img/x.bmp");
    m_o = core::Surface::OnLoad("tic_tac/img/o.bmp");
    core::Surface::Transparent(m_x,255,255,255);
    core::Surface::Transparent(m_o,255,255,255);
    m_user=XOTypes::X;
    m_winer=XOTypes::None;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            m_map[i][j]==XOTypes::None;
        }
    }
}

void TicTacGameState::OnDeactivate() {
}

void TicTacGameState::OnLoop() {
    if(m_user!= XOTypes::O || m_winer!=XOTypes::None){
        return;
    }
    
    std::vector<core::Coord> free_coords;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            if(m_map[i][j]==XOTypes::None)
                free_coords.push_back(core::Coord{i,j});
        }
    }
    
    if(free_coords.size()==0){
        return;
    }
    else{
        auto cur_pos=std::rand()%(free_coords.size()-1);
        auto c=free_coords.at(cur_pos);
        m_map[c.x][c.y]=XOTypes::O;
        m_user=XOTypes::X;
    }
}

void TicTacGameState::OnRender(SDL_Surface* Surf_Display) {
    //logger << "TicTacGameState::OnRender" << endl;
    core::Surface::OnDraw(Surf_Display, m_bg, 0, 0);

    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            SDL_Surface* cur_surface=0;
            if(m_map[i][j]==XOTypes::X)
                cur_surface=m_x;
            if(m_map[i][j]==XOTypes::O)
                cur_surface=m_o;

            core::Surface::OnDraw(Surf_Display,cur_surface,
                    i*215,j*215);
        }
    }
}

void TicTacGameState::OnLButtonDown(int mX, int mY) {
    int j=mY/215;
    int i=mX/215;

    if( m_map[i][j]!=XOTypes::None || m_winer!=XOTypes::None)
        return;

    logger<<" ticTac:leftBtn i="<< i
            <<" j="<<j<<endl;

    if(m_user== XOTypes::X){
        logger <<"set x\n";
        m_map[i][j]=XOTypes::X;
        m_user= XOTypes::O;
    }else if(m_user== XOTypes::O){
        logger <<"set o\n";
        m_map[i][j]=XOTypes::O;
        m_user= XOTypes::X;
    }
    m_winer=getWiner();
    switch(m_winer){
            case XOTypes::O:
                logger<<" winer is O\n";
                break;
            case XOTypes::X:
                logger<<" winer is X\n";
                break;
        }
}

XOTypes TicTacGameState::getWiner(){
    if(m_map[0][0]==m_map[0][1] && m_map[0][1]==m_map[0][2])
        return m_map[0][0];
    if(m_map[1][0]==m_map[1][1] && m_map[1][1]==m_map[1][2])
        return m_map[1][0];
    if(m_map[2][0]==m_map[2][1] && m_map[2][1]==m_map[2][2])
        return m_map[2][0];

    if(m_map[0][0]==m_map[1][0] && m_map[1][0]==m_map[2][0])
        return m_map[0][0];
    if(m_map[0][1]==m_map[1][1] && m_map[1][1]==m_map[2][1])
        return m_map[0][1];
    if(m_map[0][2]==m_map[1][2] && m_map[1][2]==m_map[2][2])
        return m_map[0][2];

    if(m_map[0][0]==m_map[1][1] && m_map[1][1]==m_map[2][2])
        return m_map[0][0];
    if(m_map[0][2]==m_map[1][1] && m_map[1][1]==m_map[2][0])
        return m_map[0][2];

    return XOTypes::None;
}