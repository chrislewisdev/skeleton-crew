#include "core.h"
#include "gen/intro-screen.h"

uint8_t introScreenTileBase;

void stateInitIntro() {
    HIDE_BKG;
    releaseAllBkgGfx();
    introScreenTileBase = claimBkgGfx(intro_screen_TILE_COUNT, intro_screen_tiles);
    set_bkg_tiles(0, 0, 20, 18, intro_screen_map);
    SHOW_BKG;
}

void stateUpdateIntro() {

}

