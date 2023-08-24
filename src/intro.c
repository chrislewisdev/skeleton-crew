#include <gb/metasprites.h>
#include "core.h"
#include "ui.h"

const char* introText = \
"Tired of being treated like\n\
second-class citizens,\n\
four skeletons band together\n\
to show their demon boss\n\
just how strong they can be.\n\n\
Guide them through the dungeon\n\
in their quest for equality!\n\n\
Press A to start";

void stateInitIntro() {
    HIDE_BKG;
    HIDE_SPRITES;
    stopMusic();
    releaseAllBkgGfx();
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);
    SHOW_BKG;
    renderText(1, 1, introText);
}

void stateUpdateIntro() {
    if (KEYPRESSED(J_A)) {
        queueStateSwitch(STATE_EXPLORE);
    }
}

