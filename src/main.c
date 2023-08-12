#include <gb/gb.h>
#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"

void main() {
    switchToState(STATE_SPLASH);
    while (1) {
        wait_vbl_done();

        previousInput = input;
        input = joypad();

        if (appState == STATE_SPLASH) {
            stateUpdateSplash();
        } else if (appState == STATE_TITLE) {
            stateUpdateTitle();
        } else if (appState == STATE_INTRO) {
            stateUpdateIntro();
        }
    }
}

