#include <rand.h>
#include "core.h"
#include "ui.h"
#include "gen/title-screen.h"

BANKREF_EXTERN(skeleton_cru)
extern hUGESong_t skeleton_cru;

void actionNewGame();
void actionCredits();

const MenuItem mainMenuItems[] = {
    {.description = "New game", .action = actionNewGame},
    {.description = "Load game", .action = NULL},
    {.description = "Credits", .action = actionCredits},
};
Menu mainMenu = {
    .x = 2, .y = 11,
    .width = 8, .height = 5,
    .selectedIndex = 0,
    .itemsSize = 3,
    .items = mainMenuItems,
};

uint8_t titleScreenTileBase;

void stateInitTitle() {
    HIDE_BKG;
    HIDE_SPRITES;

    SWITCH_ROM(1);

    hide_sprites_range(0, 40);

    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSharedGfx();
    releaseAllSprites();
    titleScreenTileBase = claimBkgGfx(title_screen_TILE_COUNT, title_screen_tiles);
    set_bkg_based_tiles(0, 0, 20, 18, title_screen_map, titleScreenTileBase);

    initUi();
    renderMenu(&mainMenu);

    startMusic(&skeleton_cru, BANK(skeleton_cru));

    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateTitle() {
    updateMenu(&mainMenu);
}

void actionNewGame() {
    initrand(DIV_REG);
    queueStateSwitch(STATE_INTRO);
    // Temp code: go straight into battle for testing
    //switchToState(STATE_BATTLE);
}

void actionCredits() {
    queueStateSwitch(STATE_CREDITS);
}

