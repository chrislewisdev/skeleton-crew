#include <gb/gb.h>
#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"
#include "explore.h"

void main() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    switchToState(STATE_SPLASH);
    while (1) {
        wait_vbl_done();

        hUGE_dosound();

        previousInput = input;
        input = joypad();

        if (appState == STATE_SPLASH) {
            stateUpdateSplash();
        } else if (appState == STATE_TITLE) {
            stateUpdateTitle();
        } else if (appState == STATE_INTRO) {
            stateUpdateIntro();
        } else if (appState == STATE_EXPLORE) {
            stateUpdateExplore();
        }
    }
}

