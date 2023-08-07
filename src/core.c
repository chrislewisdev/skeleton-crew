#include "core.h"

AppState appState = STATE_SPLASH;
void (*currentStateCleanup)() = NULL;

void switchToState(AppState targetState) {
    if (currentStateCleanup != NULL) {
        currentStateCleanup();
    }

    appState = targetState;
}

