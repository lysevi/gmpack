#include <Application.h>

#include "AppStateManager.h"
#include "AppStateIntro.h"

#include "TicTacGameState.h"

int main(int argc, char**argv) {
    AppStateManager::AddState(APPSTATE_INTRO, new AppStateIntro("img/intro.bmp"));
    AppStateManager::AddState(APPSTATE_GAME, new TicTacGameState());
    Application app(640, 640);
    return app.OnExecute();
}