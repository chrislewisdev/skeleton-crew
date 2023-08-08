#include "splash.h"
#include "core.h"
#include "gen/gbcompo.h"

// Private
uint8_t splashBkgBaseTile;

void stateInitSplash() {
    releaseAllBkgGfx();
    splashBkgBaseTile = claimBkgGfx(gbcompo_TILE_COUNT, gbcompo_tiles);
    set_bkg_tiles(0, 0, 20, 18, gbcompo_map);
    SHOW_BKG;
}

void stateUpdateSplash() {

}

