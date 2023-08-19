#include "core.h"
#include "ui.h"
#include "rpg.h"
#include "hUGEDriver.h"
#include "gen/battle-background.h"
#include "gen/zyme-battle.h"
#include "gen/ivan-battle.h"
#include "gen/olaf-battle.h"
#include "gen/pierre-battle.h"

extern hUGESong_t exchange_your_wits;
BANKREF_EXTERN(exchange_your_wits)

void renderStatusDisplay();
void renderParty();

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
uint8_t baseTiles[4];

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

    baseTiles[0] = claimObjGfx(zyme_battle_TILE_COUNT, zyme_battle_tiles);
    baseTiles[1] = claimObjGfx(ivan_battle_TILE_COUNT, ivan_battle_tiles);
    baseTiles[2] = claimObjGfx(olaf_battle_TILE_COUNT, olaf_battle_tiles);
    baseTiles[3] = claimObjGfx(pierre_battle_TILE_COUNT, pierre_battle_tiles);
    // Temporary-ish - set the metasprite pointers for player party
    party[0].metasprite = zyme_battle_metasprites[0];
    party[1].metasprite = ivan_battle_metasprites[0];
    party[2].metasprite = olaf_battle_metasprites[0];
    party[3].metasprite = pierre_battle_metasprites[0];

    renderStatusDisplay();
    renderMenu(&primaryMenu);
    renderParty();

    SWITCH_ROM(BANK(exchange_your_wits));
    hUGE_init(&exchange_your_wits);
    playMusic = TRUE;
    //SWITCH_ROM(1);

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

void renderParty() {
    for (uint8_t i = 0; i < 4; i++) {
        // TODO: Flesh this out properly!
        uint8_t baseSprite = claimSprites(4);
        move_metasprite(party[i].metasprite, baseTiles[i], baseSprite, 36, 32 + i * 20);
    }
}

