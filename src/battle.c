#include "core.h"
#include "ui.h"
#include "gen/battle-background.h"

void renderStatusDisplay();

MenuItem primaryMenuItems[] = {
    {.description = "Fight", .action = NULL},
    {.description = "Skill", .action = NULL},
    {.description = "Item", .action = NULL},
    {.description = "Run", .action = NULL},
};
Menu primaryMenu = {
    .x = 9, .y = 12,
    .width = 5, .height = 6,
    .selectedIndex = 0,
    .itemsSize = 4,
    .items = primaryMenuItems
};

uint8_t battleBackgroundBaseTile;

void stateInitBattle() {
    HIDE_BKG;
    HIDE_SPRITES;

    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSprites();

    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);

    initUi();

    battleBackgroundBaseTile = claimBkgGfx(battle_background_TILE_COUNT, battle_background_tiles);
    set_bkg_based_tiles(0, 0, 20, 12, battle_background_map, battleBackgroundBaseTile);

    renderStatusDisplay();
    renderMenu(&primaryMenu);

    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateBattle() {
    updateMenu(&primaryMenu);
}

void renderStatusDisplay() {
    renderText(1, 13, "Zymie:"); renderText(5, 13, "45/45");
    renderText(1, 14, "Ivan:"); renderText(5, 14, "52/52");
    renderText(1, 15, "Olaf:"); renderText(5, 15, "35/35");
    renderText(1, 16, "Pierre:"); renderText(5, 16, "14/63");
    render9slice(0, 12, 9, 6);
}

