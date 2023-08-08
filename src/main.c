#include <gb/gb.h>
#include "core.h"
#include "splash.h"

void main() {
    switchToState(STATE_SPLASH);
    while (1) {
        wait_vbl_done();

        if (appState == STATE_SPLASH) {
            stateUpdateSplash();
        }
    }
}

