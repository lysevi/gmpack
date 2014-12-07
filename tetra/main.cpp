#include <Application.h>

#include "AppStateManager.h"
#include "AppStateIntro.h"
#include "TetraGameState.h"

int main(int argc, char**argv) {
    core::AppStateManager::AddState(core::APPSTATE_INTRO, new core::AppStateIntro("img/intro.bmp",10));
    core::AppStateManager::AddState(core::APPSTATE_GAME, new TetraGameState());
    core::Application app(480, 640);
    return app.OnExecute();
}