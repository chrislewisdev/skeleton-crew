#include "core.h"
#include "ui.h"

const char* creditsText = \
"         Music\n\
           by\n\
       Nikku4211\n\n\
    Everything else \n\
           by\n\
   Chris Lewis-Hou";

void stateInitCredits() {
    HIDE_BKG;
    HIDE_SPRITES;
    releaseAllBkgGfx();
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);
    SHOW_BKG;
    renderText(4, 4, creditsText);
    renderText(1, 16, "Press B to return");
}

void stateUpdateCredits() {
    if (KEYPRESSED(J_B)) {
        switchToState(STATE_TITLE);
    }
}

