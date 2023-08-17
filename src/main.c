#include <gb/gb.h>
#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"
#include "explore.h"
#include "credits.h"
#include "battle.h"
#include "hUGEDriver.h"

uint8_t playMusic = 0;

void main() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    switchToState(STATE_SPLASH);
    while (1) {
        wait_vbl_done();

        if (playMusic) hUGE_dosound();

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
        } else if (appState == STATE_CREDITS) {
            stateUpdateCredits();
        } else if (appState == STATE_BATTLE) {
            stateUpdateBattle();
        }
    }
}

