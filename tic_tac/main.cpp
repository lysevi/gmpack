#include <Application.h>

#include "AppStateManager.h"
#include "AppStateIntro.h"

#include "TicTacGameState.h"

int main(int argc, char**argv) {
    core::AppStateManager::AddState(core::APPSTATE_INTRO, new core::AppStateIntro("tic_tac/img/intro.bmp"));
    core::AppStateManager::AddState(core::APPSTATE_GAME, new TicTacGameState());
    core::Application app(640, 640);
    return app.OnExecute();
}