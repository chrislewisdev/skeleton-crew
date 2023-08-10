#include "core.h"
#include "gen/outro-screen.h"

uint8_t outroScreenTileBase;

void stateInitOutro() {
    HIDE_BKG;
    releaseAllBkgGfx();
    outroScreenTileBase = claimBkgGfx(outro_screen_TILE_COUNT, outro_screen_tiles);
    set_bkg_tiles(0, 0, 20, 18, outro_screen_map);
    SHOW_BKG;
}

void stateUpdateOutro() {

}

