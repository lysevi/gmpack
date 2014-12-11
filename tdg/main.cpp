/* 
 * File:   main.cpp
 * Author: lsv
 *
 * Created on 10 декабря 2014 г., 21:36
 */
#include "Application.h"
#include "AppStateManager.h"
#include "AppStateIntro.h"

#include "TDGame.h"

int main(int argc, char** argv) {
    //core::AppStateManager::AddState(core::APPSTATE_INTRO, new core::AppStateIntro("img/intro.bmp",2));
    core::AppStateManager::AddState(core::APPSTATE_GAME, new TDGame());
    core::Application app(640, 640);
    return app.OnExecute();
}

