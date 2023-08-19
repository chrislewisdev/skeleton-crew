#include <rand.h>
#include "core.h"
#include "ui.h"
#include "rpg.h"
#include "hUGEDriver.h"
#include "gen/battle-background.h"
#include "gen/zyme-battle.h"
#include "gen/ivan-battle.h"
#include "gen/olaf-battle.h"
#include "gen/pierre-battle.h"

#define PARTY_LINE_X    36
#define ENEMY_LINE_X    110
#define STANDOUT_X      24

typedef struct CharacterDisplayInfo {
    uint8_t x, y;
    uint8_t baseTile, baseSprite;
    const metasprite_t* metasprite;
} CharacterDisplayInfo;

BANKREF_EXTERN(exchange_your_wits)
extern hUGESong_t exchange_your_wits;

void renderStatusDisplay();
void renderParty();
void generateEnemyParty();

MenuItem primaryMenuItems[] = {
    {.description = "Fight", .action = NULL},
    {.description = "Skill", .action = NULL},
    {.description = "Item", .action = NULL},
    {.description = "Run", .action = NULL},
};
Menu primaryMenu = {
    .x = 0, .y = 12,
    .width = 11, .height = 6,
    .selectedIndex = 0,
    .itemsSize = 4,
    .items = primaryMenuItems
};

uint8_t battleBackgroundBaseTile;
uint8_t enemyPartySize;
Character enemyParty[4];
// Might be able to unify these arrays at some point...
CharacterDisplayInfo partyDisplayInfo[4];
CharacterDisplayInfo enemyDisplayInfo[4];

void initCharacterDisplayInfo() {
    partyDisplayInfo[0].metasprite = zyme_battle_metasprites[0];
    partyDisplayInfo[0].x = PARTY_LINE_X + STANDOUT_X;
    partyDisplayInfo[0].y = 32;
    partyDisplayInfo[0].baseTile = claimObjGfx(zyme_battle_TILE_COUNT, zyme_battle_tiles);
    partyDisplayInfo[0].baseSprite = claimSprites(4);

    partyDisplayInfo[1].metasprite = ivan_battle_metasprites[0];
    partyDisplayInfo[1].x = PARTY_LINE_X;
    partyDisplayInfo[1].y = 32 + 20;
    partyDisplayInfo[1].baseTile = claimObjGfx(ivan_battle_TILE_COUNT, ivan_battle_tiles);
    partyDisplayInfo[1].baseSprite = claimSprites(4);

    partyDisplayInfo[2].metasprite = olaf_battle_metasprites[0];
    partyDisplayInfo[2].x = PARTY_LINE_X;
    partyDisplayInfo[2].y = 32 + 40;
    partyDisplayInfo[2].baseTile = claimObjGfx(olaf_battle_TILE_COUNT, olaf_battle_tiles);
    partyDisplayInfo[2].baseSprite = claimSprites(4);

    partyDisplayInfo[3].metasprite = pierre_battle_metasprites[0];
    partyDisplayInfo[3].x = PARTY_LINE_X;
    partyDisplayInfo[3].y = 32 + 60;
    partyDisplayInfo[3].baseTile = claimObjGfx(pierre_battle_TILE_COUNT, pierre_battle_tiles);
    partyDisplayInfo[3].baseSprite = claimSprites(4);

    for (uint8_t i = 0; i < enemyPartySize; i++) {
        enemyDisplayInfo[i].x = ENEMY_LINE_X;
        enemyDisplayInfo[i].y = 32 + i * 20;
        enemyDisplayInfo[i].baseSprite = claimSprites(4);
    }
}

void stateInitBattle() {
    HIDE_BKG;
    HIDE_SPRITES;
    SWITCH_ROM(1);

    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSprites();

    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);

    initUi();

    battleBackgroundBaseTile = claimBkgGfx(battle_background_TILE_COUNT, battle_background_tiles);
    set_bkg_based_tiles(0, 0, 20, 12, battle_background_map, battleBackgroundBaseTile);

    generateEnemyParty();
    initCharacterDisplayInfo();

    renderStatusDisplay();
    renderMenu(&primaryMenu);
    renderParty();

    SWITCH_ROM(BANK(exchange_your_wits));
    hUGE_init(&exchange_your_wits);
    playMusic = TRUE;

    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateBattle() {
    updateMenu(&primaryMenu);
}

void stateCleanupBattle() {
    // Reset all enemy type base tiles
    for (uint8_t i = 0; i < ENEMY_TYPE_COUNT; i++) {
        enemyTypes[i].baseTile = 0;
    }
}

void generateEnemyParty() {
    enemyPartySize = 4;
    for (uint8_t i = 0; i < enemyPartySize; i++) {
        uint8_t enemyId = rand() % ENEMY_TYPE_COUNT;
        enemyParty[i].hp = enemyTypes[enemyId].hp;
        enemyParty[i].maxHp = enemyTypes[enemyId].hp;
        enemyParty[i].atk = enemyTypes[enemyId].atk;
        enemyParty[i].def = enemyTypes[enemyId].def;
        enemyParty[i].spAtk = enemyTypes[enemyId].spAtk;
        enemyParty[i].spDef = enemyTypes[enemyId].spDef;
        
        for (uint8_t j = 0; j < 4; j++) {
            enemyParty[i].affinities[j] = enemyTypes[enemyId].affinities[j];
            enemyParty[i].skills[j] = enemyTypes[enemyId].skills[j];
        }

        enemyDisplayInfo[i].metasprite = enemyTypes[enemyId].metasprite;
        if (enemyTypes[enemyId].baseTile == 0) {
            enemyTypes[enemyId].baseTile = claimObjGfx(enemyTypes[enemyId].tileCount, enemyTypes[enemyId].tiles);
        }
        enemyDisplayInfo[i].baseTile = enemyTypes[enemyId].baseTile;
    }
}

void renderStatusDisplay() {
    renderText(12, 13, "Zymie:"); renderText(16, 13, "45/45");
    renderText(12, 14, "Ivan:"); renderText(16, 14, "52/52");
    renderText(12, 15, "Olaf:"); renderText(16, 15, "35/35");
    renderText(12, 16, "Pierre:"); renderText(16, 16, "14/63");
    render9slice(11, 12, 9, 6);
}

void renderParty() {
    for (uint8_t i = 0; i < 4; i++) {
        move_metasprite(
            partyDisplayInfo[i].metasprite,
            partyDisplayInfo[i].baseTile,
            partyDisplayInfo[i].baseSprite,
            partyDisplayInfo[i].x,
            partyDisplayInfo[i].y
        );
    }
    for (uint8_t i = 0; i < enemyPartySize; i++) {
        move_metasprite(
            enemyDisplayInfo[i].metasprite,
            enemyDisplayInfo[i].baseTile,
            enemyDisplayInfo[i].baseSprite,
            enemyDisplayInfo[i].x,
            enemyDisplayInfo[i].y
        );
    }
}

