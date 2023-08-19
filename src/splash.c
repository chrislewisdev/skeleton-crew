#include "splash.h"
#include "core.h"
#include "gen/gbcompo.h"

#define STEP_DURATION   20

uint8_t splashBkgBaseTile;
uint8_t step;
uint8_t stepTimer;

void stateInitSplash() {
    releaseAllBkgGfx();
    splashBkgBaseTile = claimBkgGfx(gbcompo_TILE_COUNT, gbcompo_tiles);
    set_bkg_based_tiles(0, 0, 20, 18, gbcompo_map, splashBkgBaseTile);

    BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_WHITE, DMG_WHITE);
    
    SHOW_BKG;

    step = 0;
    stepTimer = 0;
}
 
void stateUpdateSplash() {
    if (stepTimer == 0) {
        if (step == 1) {
            BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY);
        } else if (step == 2) {
            BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY);
        } else if (step == 3) {
            BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
        } else if (step == 6) {
            queueStateSwitch(STATE_TITLE);
        }
        step++;
        stepTimer = STEP_DURATION;
    }
    stepTimer--;
}

