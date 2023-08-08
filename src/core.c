#include "core.h"
#include "splash.h"

// Public variables
AppState appState = STATE_SPLASH;
void (*currentStateCleanup)() = NULL;

// Private variables
uint8_t gfxTileOffset = 0;

void switchToState(AppState targetState) {
    if (currentStateCleanup != NULL) {
        currentStateCleanup();
    }

    if (targetState == STATE_SPLASH) {
        stateInitSplash();
    }

    appState = targetState;
}

inline uint8_t claimBkgGfx(uint8_t numTiles, const uint8_t *data) {
    uint8_t baseTile = gfxTileOffset;
    gfxTileOffset += numTiles;
    set_bkg_data(baseTile, numTiles, data);
    return baseTile;
}

inline void releaseAllBkgGfx() {
    gfxTileOffset = 0;
}

