#include "core.h"
#include "ui.h"

const char* creditsText = \
"         Music\n\
           by\n\
       Nikku4211\n\n\
        Code/Art \n\
           by\n\
   Chris Lewis-Hou\n\n\
 Uses hUGEDriver and\n\
   toxa's vwf code\n\n\
     Special thanks\n\
  WP, Skeets, and Nim";

void stateInitCredits() {
    HIDE_BKG;
    HIDE_SPRITES;
    releaseAllBkgGfx();
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);
    SHOW_BKG;
    renderText(4, 1, creditsText);
    renderText(1, 16, "Press B to return");
}

void stateUpdateCredits() {
    if (KEYPRESSED(J_B)) {
        queueStateSwitch(STATE_TITLE);
    }
}

