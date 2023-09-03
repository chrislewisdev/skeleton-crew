#include "core.h"
#include "ui.h"

BANKREF_EXTERN(gold_star)
extern hUGESong_t gold_star;

const char *outroText = \
"The tyrannical demon defeated,\n\
our four heroes sought to\n\
improve life for all monsters.\n\n\
Hour-long lunch breaks were\n\
instituted, the kitchen was\n\
expanded, and they bought a\n\
pool table.\n\n\
To this day, annual pool\n\
tournaments are held in their\n\
honour.\n\n\
The end. Thanks for playing!";

void stateInitOutro() {
    HIDE_BKG;
    HIDE_SPRITES;
    stopMusic();
    releaseAllBkgGfx();
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);
    startMusic(&gold_star, BANK(gold_star));
    SHOW_BKG;
    renderText(1, 1, outroText);
}

void stateUpdateOutro() {
    //if (KEYPRESSED(J_A)) queueStateSwitch(STATE_TITLE);
}

