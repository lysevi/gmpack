#include <Application.h>

#include "AppStateManager.h"
#include "AppStateIntro.h"
#include "TetraGameState.h"

int main(int argc, char**argv) {
    AppStateManager::AddState(APPSTATE_INTRO, new AppStateIntro("img/intro.bmp",1000));
    AppStateManager::AddState(APPSTATE_GAME, new TetraGameState());
    Application app(640, 640);
    return app.OnExecute();
}