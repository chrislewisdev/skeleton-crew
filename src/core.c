#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"
#include "outro.h"
#include "explore.h"
#include "credits.h"
#include "battle.h"

// Public variables
AppState appState = STATE_SPLASH;
void (*currentStateCleanup)() = NULL;

uint8_t input, previousInput;

uint8_t gfxTileOffset = 1;
uint8_t objTileOffset = 1;
uint8_t spriteOffset = 0;

void switchToState(AppState targetState) {
    if (currentStateCleanup != NULL) {
        currentStateCleanup();
        currentStateCleanup = NULL;
    }

    if (targetState == STATE_SPLASH) {
        stateInitSplash();
    } else if (targetState == STATE_TITLE) {
        stateInitTitle();
    } else if (targetState == STATE_INTRO) {
        stateInitIntro();
    } else if (targetState == STATE_OUTRO) {
        stateInitOutro();
    } else if (targetState == STATE_EXPLORE) {
        stateInitExplore();
    } else if (targetState == STATE_CREDITS) {
        stateInitCredits();
    } else if (targetState == STATE_BATTLE) {
        stateInitBattle();
        currentStateCleanup = stateCleanupBattle;
    }

    appState = targetState;
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

