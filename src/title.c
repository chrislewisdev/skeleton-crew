#include "core.h"
#include "ui.h"
#include "gen/title-screen.h"

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

    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSprites();
    titleScreenTileBase = claimBkgGfx(title_screen_TILE_COUNT, title_screen_tiles);
    set_bkg_based_tiles(0, 0, 20, 18, title_screen_map, titleScreenTileBase);

    initUi();
    renderMenu(&mainMenu);

    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateTitle() {
    updateMenu(&mainMenu);
}

void actionNewGame() {
    //switchToState(STATE_INTRO);
    // Temp code: go straight into battle for testing
    switchToState(STATE_BATTLE);
}

void actionCredits() {
    switchToState(STATE_CREDITS);
}

