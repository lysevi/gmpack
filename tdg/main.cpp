/* 
 * File:   main.cpp
 * Author: lsv
 *
 * Created on 10 декабря 2014 г., 21:36
 */
#include "App/Application.h"
#include "App/AppStateManager.h"
#include "App/AppStateIntro.h"

#include "TDGame.h"

int main(int argc, char** argv) {
    //core::AppStateManager::AddState(core::APPSTATE_INTRO, new core::AppStateIntro("img/intro.bmp",2));
    core::AppStateManager::AddState(core::APPSTATE_GAME, new TDGame(800,600,640,480));
    core::Application app(800, 600);
    return app.OnExecute();
}

