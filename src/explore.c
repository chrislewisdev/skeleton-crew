#include "core.h"
#include "gen/tiles.h"
#include "gen/metamap.h"
#include "gen/zymie.h"

#define SCREEN_WIDTH        20
#define SCREEN_HEIGHT       18
#define META_SCREEN_WIDTH   10
#define META_SCREEN_HEIGHT  9
#define METAMAP_WIDTH       (metamap_WIDTH / metamap_TILE_W)
#define METAMAP_HEIGHT      (metamap_HEIGHT / metamap_TILE_H)

typedef struct Point { uint8_t x; uint8_t y; } Point;

uint8_t tilesBase;
uint8_t zymieBaseTile, zymieBaseSprite;
Point player = {.x = 4, .y = 4};

inline void renderMetamap(uint8_t, uint8_t);
inline void renderPlayer();
inline uint8_t isTileSolid(uint8_t, uint8_t);

void stateInitExplore() {
    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSprites();

    tilesBase = claimBkgGfx(tiles_TILE_COUNT, tiles_tiles);
    zymieBaseTile = claimObjGfx(zymie_TILE_COUNT, zymie_tiles);
    zymieBaseSprite = claimSprites(4);

    renderMetamap(0, 0);
    renderPlayer();
    
    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateExplore() {
    if (KEYPRESSED(J_UP) && !isTileSolid(player.x, player.y - 1)) {
        player.y--;
        renderPlayer();
    } else if (KEYPRESSED(J_DOWN) && !isTileSolid(player.x, player.y + 1)) {
        player.y++;
        renderPlayer();
    } else if (KEYPRESSED(J_LEFT) && !isTileSolid(player.x - 1, player.y)) {
        player.x--;
        renderPlayer();
    } else if (KEYPRESSED(J_RIGHT) && !isTileSolid(player.x + 1, player.y)) {
        player.x++;
        renderPlayer();
    }
}

inline uint8_t getMetaTile(uint8_t x, uint8_t y) {
    return metamap_map[x + y * METAMAP_WIDTH];
}

inline uint8_t isTileSolid(uint8_t x, uint8_t y) {
    return getMetaTile(x, y) != 2;
}

inline void renderPlayer() {
    move_metasprite(zymie_metasprites[0], zymieBaseTile, zymieBaseSprite, player.x * 16 + 8, player.y * 16 + 16);
}

inline void renderMetatile(uint8_t x, uint8_t y, uint8_t tileId) {
    set_bkg_tile_xy(x * 2, y * 2, tileId * 4 + tilesBase);
    set_bkg_tile_xy(x * 2 + 1, y * 2, tileId * 4 + tilesBase + 1);
    set_bkg_tile_xy(x * 2, y * 2 + 1, tileId * 4 + tilesBase + 2);
    set_bkg_tile_xy(x * 2 + 1, y * 2 + 1, tileId * 4 + tilesBase + 3);
}

inline void renderMetamap(uint8_t bx, uint8_t by) {
    for (uint8_t x = bx; x < META_SCREEN_WIDTH; x++) {
        for (uint8_t y = by; y < META_SCREEN_HEIGHT; y++) {
            renderMetatile(x, y, getMetaTile(x, y));
        }
    }
}

