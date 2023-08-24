#include "core.h"
#include "battle.h"

BANKREF_EXTERN(exchange_your_wits)
extern hUGESong_t exchange_your_wits;
BANKREF_EXTERN(demon_destruction)
extern hUGESong_t demon_destruction;

AppState transitionTarget;
uint8_t frameCounter, columnIndex, rowIndex;

void stateInitTransition() {
    HIDE_SPRITES;

    frameCounter = 0;
    rowIndex = 0;

    if (triggerBossBattle) {
        startMusic(&demon_destruction, BANK(demon_destruction));
    } else {
        startMusic(&exchange_your_wits, BANK(exchange_your_wits));
    }
}

void stateUpdateTransition() {
    if (++frameCounter % 2 == 0) {
        if (rowIndex < 18) {
            fill_bkg_rect(SCX_REG / 8, (SCY_REG / 8 + rowIndex) % 32, 20, 1, 0);
            rowIndex++;
        } else {
            queueStateSwitch(transitionTarget);
        }
    }
}

