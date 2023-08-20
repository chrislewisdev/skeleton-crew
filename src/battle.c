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

#define AI_ACTION_DURATION  60

typedef struct CharacterDisplayInfo {
    uint8_t visible;
    uint8_t x, y;
    uint8_t baseTile, baseSprite;
    const metasprite_t* metasprite;
} CharacterDisplayInfo;

typedef enum UiMode {
    PRIMARY,
    SUB,
    TARGETING
} UiMode;

BANKREF_EXTERN(exchange_your_wits)
extern hUGESong_t exchange_your_wits;

void renderStatusDisplay();
void renderParties();
void generateEnemyParty();
void actionRun();
void actionFight();
void updateTargeting();
void updateTurn();

MenuItem primaryMenuItems[] = {
    {.description = "Fight", .action = actionFight},
    {.description = "Skill", .action = NULL},
    {.description = "Item", .action = NULL},
    {.description = "Run", .action = actionRun},
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
UiMode uiMode = PRIMARY;
uint8_t targetingIndex = 0;
Character* turnOrder[8] = {
    &party[0],
    &enemyParty[0],
    &party[1],
    &enemyParty[1],
    &party[2],
    &enemyParty[2],
    &party[3],
    &enemyParty[3]
};
uint8_t turnOrderSize = 8;
uint8_t turnOrderIndex = 0;
Character* currentTurnCharacter = &party[0];
Character* currentActionTarget = NULL;
uint8_t playerHasActed = FALSE;
void (*queuedAction)();
uint8_t aiActionTimer = AI_ACTION_DURATION;

void initCharacterDisplayInfo() {
    partyDisplayInfo[0].visible = (party[0].hp > 0) ? TRUE : FALSE;
    partyDisplayInfo[0].metasprite = zyme_battle_metasprites[0];
    partyDisplayInfo[0].x = PARTY_LINE_X + STANDOUT_X;
    partyDisplayInfo[0].y = 32;
    partyDisplayInfo[0].baseTile = claimObjGfx(zyme_battle_TILE_COUNT, zyme_battle_tiles);
    partyDisplayInfo[0].baseSprite = claimSprites(4);

    partyDisplayInfo[1].visible = (party[1].hp > 0) ? TRUE : FALSE;
    partyDisplayInfo[1].metasprite = ivan_battle_metasprites[0];
    partyDisplayInfo[1].x = PARTY_LINE_X;
    partyDisplayInfo[1].y = 32 + 20;
    partyDisplayInfo[1].baseTile = claimObjGfx(ivan_battle_TILE_COUNT, ivan_battle_tiles);
    partyDisplayInfo[1].baseSprite = claimSprites(4);

    partyDisplayInfo[2].visible = (party[2].hp > 0) ? TRUE : FALSE;
    partyDisplayInfo[2].metasprite = olaf_battle_metasprites[0];
    partyDisplayInfo[2].x = PARTY_LINE_X;
    partyDisplayInfo[2].y = 32 + 40;
    partyDisplayInfo[2].baseTile = claimObjGfx(olaf_battle_TILE_COUNT, olaf_battle_tiles);
    partyDisplayInfo[2].baseSprite = claimSprites(4);

    partyDisplayInfo[3].visible = (party[3].hp > 0) ? TRUE : FALSE;
    partyDisplayInfo[3].metasprite = pierre_battle_metasprites[0];
    partyDisplayInfo[3].x = PARTY_LINE_X;
    partyDisplayInfo[3].y = 32 + 60;
    partyDisplayInfo[3].baseTile = claimObjGfx(pierre_battle_TILE_COUNT, pierre_battle_tiles);
    partyDisplayInfo[3].baseSprite = claimSprites(4);

    for (uint8_t i = 0; i < enemyPartySize; i++) {
        enemyDisplayInfo[i].visible = TRUE;
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

    move_bkg(0, 0);
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);

    initUi();

    battleBackgroundBaseTile = claimBkgGfx(battle_background_TILE_COUNT, battle_background_tiles);
    set_bkg_based_tiles(0, 0, 20, 12, battle_background_map, battleBackgroundBaseTile);

    generateEnemyParty();
    initCharacterDisplayInfo();

    renderStatusDisplay();
    renderMenu(&primaryMenu);
    renderParties();

    SWITCH_ROM(BANK(exchange_your_wits));
    hUGE_init(&exchange_your_wits);
    playMusic = TRUE;

    turnOrderIndex = 0;
    currentTurnCharacter = &party[0];
    targetingIndex = 0;

    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateBattle() {
    if (currentTurnCharacter->isAlly) {
        if (uiMode == PRIMARY) {
            updateMenu(&primaryMenu);
        } else if (uiMode == TARGETING) {
            updateTargeting();
        }
    } else {
        renderCursor(0, 0);
    }
    updateTurn();
}

void stateCleanupBattle() {
    // Reset all enemy type base tiles
    for (uint8_t i = 0; i < ENEMY_TYPE_COUNT; i++) {
        enemyTypes[i].baseTile = 0;
    }
}

void actionRun() {
    queueStateSwitch(STATE_EXPLORE);
}

void actionExecuteAttack() {
    uint8_t dmg = calculateDmg(currentActionTarget, currentTurnCharacter, 5, PHYSICAL);

    if (dmg > currentActionTarget->hp) {
        currentActionTarget->hp = 0;
    } else {
        currentActionTarget->hp -= dmg;
    }
}

void actionFight() {
    queuedAction = actionExecuteAttack;
    uiMode = TARGETING;
}

void generateEnemyParty() {
    for (uint8_t i = 0; i < 4; i++) {
        enemyParty[i].hp = 0;
    }

    enemyPartySize = rand() % 3 + 1;
    for (uint8_t i = 0; i < enemyPartySize; i++) {
        uint8_t enemyId = rand() % ENEMY_TYPE_COUNT;
        enemyParty[i].isAlly = FALSE;
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
    renderText(12, 13, "Zymie:"); //renderText(16, 13, "45/45");
    renderNumber(16, 13, party[0].hp);
    renderText(12, 14, "Ivan:"); //renderText(16, 14, "52/52");
    renderNumber(16, 14, party[1].hp);
    renderText(12, 15, "Olaf:"); //renderText(16, 15, "35/35");
    renderNumber(16, 15, party[2].hp);
    renderText(12, 16, "Pierre:"); //renderText(16, 16, "14/63");
    renderNumber(16, 16, party[3].hp);
    render9slice(11, 12, 9, 6);
}

void updateStatusDisplay() {
    renderNumber(16, 13, party[0].hp);
    renderNumber(16, 14, party[1].hp);
    renderNumber(16, 15, party[2].hp);
    renderNumber(16, 16, party[3].hp);
}

void renderParties() {
    for (uint8_t i = 0; i < 4; i++) {
        if (partyDisplayInfo[i].visible) {
            move_metasprite(
                partyDisplayInfo[i].metasprite,
                partyDisplayInfo[i].baseTile,
                partyDisplayInfo[i].baseSprite,
                partyDisplayInfo[i].x,
                partyDisplayInfo[i].y
            );
        } else {
            hide_metasprite(partyDisplayInfo[i].metasprite, partyDisplayInfo[i].baseSprite);
        }
    }
    for (uint8_t i = 0; i < enemyPartySize; i++) {
        if (enemyDisplayInfo[i].visible) {
            move_metasprite(
                enemyDisplayInfo[i].metasprite,
                enemyDisplayInfo[i].baseTile,
                enemyDisplayInfo[i].baseSprite,
                enemyDisplayInfo[i].x,
                enemyDisplayInfo[i].y
            );
        } else {
            hide_metasprite(enemyDisplayInfo[i].metasprite, enemyDisplayInfo[i].baseSprite);
        }
    }
}

void updateTargeting() {
    uint8_t minAliveEnemyIndex = 0;
    uint8_t maxAliveEnemyIndex = enemyPartySize - 1;

    while (enemyParty[minAliveEnemyIndex].hp == 0) {
        minAliveEnemyIndex++;
    }
    while (enemyParty[maxAliveEnemyIndex].hp == 0) {
        maxAliveEnemyIndex--;
    }

    if (targetingIndex < minAliveEnemyIndex) targetingIndex = minAliveEnemyIndex;
    if (targetingIndex > maxAliveEnemyIndex) targetingIndex = maxAliveEnemyIndex;

    while (enemyParty[targetingIndex].hp == 0) {
        targetingIndex--;
    }

    if (KEYPRESSED(J_UP) && targetingIndex > minAliveEnemyIndex) {
        do {
            targetingIndex--;
        } while (enemyParty[targetingIndex].hp == 0 && targetingIndex > 0);
    } else if (KEYPRESSED(J_DOWN) && targetingIndex < maxAliveEnemyIndex) {
        do {
            targetingIndex++;
        } while (enemyParty[targetingIndex].hp == 0 && targetingIndex < 3);
    }

    if (KEYPRESSED(J_A)) {
        currentActionTarget = &enemyParty[targetingIndex];
        queuedAction();
        playerHasActed = TRUE;
        uiMode = PRIMARY;
    } else if (KEYPRESSED(J_B)) {
        uiMode = PRIMARY;
    }

    renderCursor(100, 36 + targetingIndex * 18);
}

void updatePartyDisplayInfo() {
    for (uint8_t i = 0; i < 4; i++) {
        partyDisplayInfo[i].visible = (party[i].hp > 0) ? TRUE : FALSE;
        if (currentTurnCharacter == &party[i]) {
            partyDisplayInfo[i].x = PARTY_LINE_X + STANDOUT_X;
        } else {
            partyDisplayInfo[i].x = PARTY_LINE_X;
        }
    }
    for (uint8_t i = 0; i < 4; i++) {
        enemyDisplayInfo[i].visible = (enemyParty[i].hp > 0) ? TRUE : FALSE;
        if (currentTurnCharacter == &enemyParty[i]) {
            enemyDisplayInfo[i].x = ENEMY_LINE_X - STANDOUT_X;
        } else {
            enemyDisplayInfo[i].x = ENEMY_LINE_X;
        }
    }
}

inline uint8_t isBattleWon() {
    for (uint8_t i = 0; i < 4; i++) {
        if (enemyParty[i].hp > 0) return FALSE;
    }
    return TRUE;
}

inline uint8_t isBattleLost() {
    for (uint8_t i = 0; i < 4; i++) {
        if (party[i].hp > 0) return FALSE;
    }
    return TRUE;
}

void onTurnEnd() {
    if (isBattleWon()) {
        queueStateSwitch(STATE_EXPLORE);
    }

    do {
        turnOrderIndex++;
        if (turnOrderIndex >= turnOrderSize) {
            turnOrderIndex = 0;
        }
    } while (turnOrder[turnOrderIndex]->hp == 0);
    currentTurnCharacter = turnOrder[turnOrderIndex];

    updatePartyDisplayInfo();
    renderParties();
    updateStatusDisplay();
}

void updateTurn() {
    if (!currentTurnCharacter->isAlly) {
        if (aiActionTimer == 0) {
            // TODO: Make sure they only target alive characters!
            currentActionTarget = &party[rand() % 4];
            actionExecuteAttack();
            onTurnEnd();
            aiActionTimer = AI_ACTION_DURATION;
        } else {
            aiActionTimer--;
        }
    } else {
        // Wait for the player to act
        if (playerHasActed) {
            onTurnEnd();
            playerHasActed = FALSE;
        }
    }
}

