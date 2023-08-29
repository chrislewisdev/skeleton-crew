#include <rand.h>
#include "core.h"
#include "ui.h"
#include "rpg.h"
#include "save.h"
#include "explore.h"
#include "gen/title-screen.h"

BANKREF_EXTERN(skeleton_cru)
extern hUGESong_t skeleton_cru;

void actionNewGame();
void actionLoadGame();
void actionCredits();

const MenuItem mainMenuItems[] = {
    {.description = "New game", .action = actionNewGame},
    {.description = "Load game", .action = actionLoadGame},
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

    // There is almost definitely a better place to put this...
    for (uint8_t i = 0; i < 4; i++) {
        party[i].growthFunction(&party[i]);
    }
    player.x = 8; player.y = 7;

    queueStateSwitch(STATE_INTRO);
}

void actionLoadGame() {
    ENABLE_RAM_MBC5;
    if (hasSaveData()) {
        loadData();
        queueStateSwitch(STATE_EXPLORE);
    }
}

void actionCredits() {
    queueStateSwitch(STATE_CREDITS);
}

