#include <gb/gb.h>
#include <rand.h>
#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"
#include "explore.h"
#include "credits.h"
#include "battle.h"
#include "hUGEDriver.h"

uint8_t playMusic = 0;
uint8_t musicBank = 2;

void main() {
    // Enable sound
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    queueStateSwitch(STATE_SPLASH);
    while (1) {
        wait_vbl_done();

        if (playMusic) {
            SWITCH_ROM(musicBank);
            hUGE_dosound();
            SWITCH_ROM(1);
        }

        previousInput = input;
        input = joypad();

        runStepFunctions();
        checkStateSwitch();
        currentStateUpdate();
    }
}

