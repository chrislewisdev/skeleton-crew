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

void main() {
    // Enable sound
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    initrand(15);

    queueStateSwitch(STATE_SPLASH);
    while (1) {
        wait_vbl_done();

        checkStateSwitch();

        if (playMusic) hUGE_dosound();

        previousInput = input;
        input = joypad();

        currentStateUpdate();
    }
}

