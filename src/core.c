#include "core.h"
#include "splash.h"
#include "title.h"
#include "intro.h"
#include "outro.h"
#include "explore.h"
#include "credits.h"
#include "battle.h"

typedef struct StepFunction {
    uint8_t (*function)(uint8_t);
    uint8_t step;
} StepFunction;

// Public variables
AppState appState = STATE_NONE, queuedTargetState = STATE_NONE;
void (*currentStateUpdate)() = NULL;
void (*currentStateCleanup)() = NULL;

uint8_t input, previousInput;

uint8_t gfxTileOffset = 1;
uint8_t objTileOffset = 1;
uint8_t spriteOffset = 0;
uint8_t sharedTileOffset = 255;

StepFunction stepFunctions[4] = {{.function = NULL, .step = 0}};

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

inline void startMusic(hUGESong_t* song, uint8_t bank) {
    NR52_REG = 0x80;
    musicBank = bank;
    playMusic = TRUE;
    SWITCH_ROM(bank);
    hUGE_init(song);
    SWITCH_ROM(1);
}
inline void stopMusic() {
    NR52_REG = 0x00;
    playMusic = FALSE;
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

inline uint8_t claimSharedGfx(uint8_t numTiles, const uint8_t* data) {
    sharedTileOffset -= numTiles;
    set_bkg_data(sharedTileOffset, numTiles, data);
    return sharedTileOffset;
}
inline void releaseAllSharedGfx() {
    sharedTileOffset = 255;
}

inline void startStepFunction(uint8_t (*function)(uint8_t)) {
    for (uint8_t i = 0; i < 4; i++) {
        if (stepFunctions[i].function == NULL) {
            stepFunctions[i].function = function;
            stepFunctions[i].step = 0;
            return;
        }
    }
}

inline void runStepFunctions() {
    for (uint8_t i = 0; i < 4; i++) {
        if (stepFunctions[i].function != NULL) {
            uint8_t finished = stepFunctions[i].function(stepFunctions[i].step++);
            if (finished) stepFunctions[i].function = NULL;
        }
    }
}

