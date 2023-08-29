#include "core.h"
#include "ui.h"
#include "vwf.h"
#include "rpg.h"
#include "save.h"

uint8_t animationFinished = FALSE;

uint8_t sfShowDialogBox(uint8_t step) {
    if (WY_REG > 96) {
        scroll_win(0, -3);
        return 0;
    } else {
        animationFinished = TRUE;
        return 1;
    }
}

uint8_t sfHideDialogBox(uint8_t step) {
    if (WY_REG < 144) {
        scroll_win(0, 3);
        return 0;
    } else {
        queueStateSwitch(STATE_EXPLORE);
        return 1;
    }
}

void stateInitFountain() {
    // Assume we are coming from explore state and relevant UI data is loaded...

    render9sliceToWindow(0, 0, 20, 6);
    vwf_set_destination(VWF_RENDER_WIN);
    vwf_draw_text(1, 1, gfxTileOffset, "The fountain heals your wounds.\nYour progress is saved.");
    move_win(8, 144);
    vwf_set_destination(VWF_RENDER_BKG);
    SHOW_WIN;

    animationFinished = FALSE;
    startStepFunction(sfShowDialogBox);

    // Healing
    for (uint8_t i = 0; i < 4; i++) {
        party[i].hp = party[i].maxHp;
    }

    saveData();
}

void stateUpdateFountain() {
    if (KEYDOWN(J_A) && animationFinished) startStepFunction(sfHideDialogBox);
}

