#include "core.h"
#include "ui.h"
#include "battle.h"
#include "hUGEDriver.h"

BANKREF_EXTERN(gameover)
extern hUGESong_t gameover;
BANKREF_EXTERN(victory_song)
extern hUGESong_t victory_song;

void stateInitPostBattle() {
    // ASSUME WE JUST CAME FROM THE BATTLE STATE AND ALL UI ASSETS ARE LOADED
    
    HIDE_SPRITES;
    
    render9slice(4, 3, 12, 10);
    fill_bkg_rect(5, 4, 10, 8, 0);

    if (battleOutcome == OUTCOME_DEFEAT) {
        startMusic(&gameover, BANK(gameover));
        renderText(8, 4, "Defeat...");
    } else if (battleOutcome == OUTCOME_ESCAPED) {
        renderText(8, 4, "Escaped!");
        renderText(5, 6, "XP Gained:"); renderNumber(13, 6, xpGained);
    } else if (battleOutcome == OUTCOME_VICTORY) {
        startMusic(&victory_song, BANK(victory_song));
        renderText(8, 4, "Victory!");
        renderText(5, 6, "XP Gained:"); renderNumber(13, 6, xpGained);
    }

    // TODO: Award XP and trigger level-ups and stuff...
}

void stateUpdatePostBattle() {
    if (KEYPRESSED(J_A)) {
        if (battleOutcome == OUTCOME_DEFEAT)
            queueStateSwitch(STATE_TITLE);
        else
            queueStateSwitch(STATE_EXPLORE);
    }
}

