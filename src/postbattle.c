#include "core.h"
#include "ui.h"
#include "battle.h"

void stateInitPostBattle() {
    // ASSUME WE JUST CAME FROM THE BATTLE STATE AND ALL UI ASSETS ARE LOADED
    
    HIDE_SPRITES;
    
    render9slice(4, 3, 12, 10);
    fill_bkg_rect(5, 4, 10, 8, 0);
    renderText(8, 4, "Victory!");
    renderText(5, 6, "XP Gained:"); renderNumber(13, 6, xpGained);

    // TODO: Award XP and trigger level-ups and stuff...
}

void stateUpdatePostBattle() {
    if (KEYPRESSED(J_A)) queueStateSwitch(STATE_EXPLORE);
}

