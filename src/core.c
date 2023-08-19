#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"
#include "outro.h"
#include "explore.h"
#include "credits.h"
#include "battle.h"

// Public variables
AppState appState = STATE_NONE, queuedTargetState = STATE_NONE;
void (*currentStateUpdate)() = NULL;
void (*currentStateCleanup)() = NULL;

uint8_t input, previousInput;

uint8_t gfxTileOffset = 1;
uint8_t objTileOffset = 1;
uint8_t spriteOffset = 0;

inline void queueStateSwitch(AppState targetState) {
    queuedTargetState = targetState;
}

void checkStateSwitch() {
    if (queuedTargetState == appState) return;

    if (currentStateCleanup != NULL) {
        currentStateCleanup();
        currentStateCleanup = NULL;
    }

    if (queuedTargetState == STATE_SPLASH) {
        stateInitSplash();
        currentStateUpdate = stateUpdateSplash;
    } else if (queuedTargetState == STATE_TITLE) {
        stateInitTitle();
        currentStateUpdate = stateUpdateTitle;
    } else if (queuedTargetState == STATE_INTRO) {
        stateInitIntro();
        currentStateUpdate = stateUpdateIntro;
    } else if (queuedTargetState == STATE_OUTRO) {
        stateInitOutro();
        currentStateUpdate = stateUpdateOutro;
    } else if (queuedTargetState == STATE_EXPLORE) {
        stateInitExplore();
        currentStateUpdate = stateUpdateExplore;
    } else if (queuedTargetState == STATE_CREDITS) {
        stateInitCredits();
        currentStateUpdate = stateUpdateCredits;
    } else if (queuedTargetState == STATE_BATTLE) {
        stateInitBattle();
        currentStateUpdate = stateUpdateBattle;
        currentStateCleanup = stateCleanupBattle;
    }

    appState = queuedTargetState;
}

inline uint8_t claimBkgGfx(uint8_t numTiles, const uint8_t *data) {
    uint8_t baseTile = gfxTileOffset;
    gfxTileOffset += numTiles;
    set_bkg_data(baseTile, numTiles, data);
    return baseTile;
}

inline uint8_t claimBkgGfxRaw(uint8_t numTiles) {
    uint8_t baseTile = gfxTileOffset;
    gfxTileOffset += numTiles;
    return baseTile;
}

inline void releaseAllBkgGfx() {
    gfxTileOffset = 1;
}

inline uint8_t claimObjGfx(uint8_t numTiles, const uint8_t *data) {
    uint8_t baseTile = objTileOffset;
    objTileOffset += numTiles;
    set_sprite_data(baseTile, numTiles, data);
    return baseTile;
}

inline void releaseAllObjGfx() {
    objTileOffset = 1;
}

inline uint8_t claimSprite() {
    return spriteOffset++;
}

inline uint8_t claimSprites(uint8_t numSprites) {
    uint8_t baseSprite = spriteOffset;
    spriteOffset += numSprites;
    return baseSprite;
}

inline void releaseAllSprites() {
    spriteOffset = 0;
}

