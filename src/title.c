#include "core.h"
#include "ui.h"
#include "gen/title-screen.h"

const MenuItem mainMenuItems[] = {
    {.tagId = 0, .action = NULL}, // New game
    {.tagId = 1, .action = NULL}, // Load game
    // Credits?
};
Menu mainMenu = {
    .x = 3, .y = 11,
    .width = 5, .height = 5,
    .selectedIndex = 0,
    .itemsSize = 2,
    .items = mainMenuItems,
};

uint8_t titleScreenTileBase;

void stateInitTitle() {
    HIDE_BKG;

    releaseAllBkgGfx();
    titleScreenTileBase = claimBkgGfx(title_screen_TILE_COUNT, title_screen_tiles);
    set_bkg_tiles(0, 0, 20, 18, title_screen_map);

    initUi();
    renderMenu(&mainMenu);

    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateTitle() {
    updateMenu(&mainMenu);
}

