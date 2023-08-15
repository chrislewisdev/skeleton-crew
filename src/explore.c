#include "core.h"
#include "gen/tiles.h"
#include "gen/metamap.h"
#include "gen/zymie.h"

#define SCREEN_WIDTH        20
#define SCREEN_HEIGHT       18
#define META_SCREEN_WIDTH   10
#define META_SCREEN_HEIGHT  9
#define META_TILEMAP_WIDTH  16
#define META_TILEMAP_HEIGHT 16
#define METAMAP_WIDTH       (metamap_WIDTH / metamap_TILE_W)
#define METAMAP_HEIGHT      (metamap_HEIGHT / metamap_TILE_H)

typedef struct Point { uint8_t x; uint8_t y; } Point;
typedef struct Bounds { uint8_t left, right, top, bottom; } Bounds;

typedef enum Facing { F_UP, F_DOWN, F_LEFT, F_RIGHT } Facing;

uint8_t tilesBase;
uint8_t zymieBaseTile, zymieBaseSprite;
Point player = {.x = 3, .y = 2};
Point metaCamera = {.x = 0, .y = 2};
Bounds viewport = {.left = 0, .right = META_SCREEN_WIDTH - 1, .top = 0, .bottom = META_SCREEN_HEIGHT - 1};
Bounds renderedMap = {.left = 0, .right = META_SCREEN_WIDTH - 1, .top = 0, .bottom = META_SCREEN_HEIGHT - 1};
Facing playerFacing = F_DOWN;

inline void renderMetamap(uint8_t, uint8_t);
inline void renderColumn(uint8_t, uint8_t, uint8_t, uint8_t);
inline void renderRow(uint8_t, uint8_t, uint8_t, uint8_t);
inline void renderPlayer();
inline uint8_t isTileSolid(uint8_t, uint8_t);
void updateCamera();
void move(Facing direction);

void stateInitExplore() {
    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSprites();

    tilesBase = claimBkgGfx(tiles_TILE_COUNT, tiles_tiles);
    zymieBaseTile = claimObjGfx(zymie_TILE_COUNT, zymie_tiles);
    zymieBaseSprite = claimSprites(4);

//    updateCamera();
    renderPlayer();
    renderMetamap(0, 0);
    
    SHOW_BKG;
    SHOW_SPRITES;
}

void stateUpdateExplore() {
    if (KEYPRESSED(J_UP)) {
        playerFacing = F_UP;
        if (!isTileSolid(player.x, player.y - 1)) {
            move(F_UP);
        }
        //renderPlayer();
    } else if (KEYPRESSED(J_DOWN)) {
        playerFacing = F_DOWN;
        if (!isTileSolid(player.x, player.y + 1)) {
            move(F_DOWN);
        }
        //renderPlayer();
    } else if (KEYPRESSED(J_LEFT)) {
        playerFacing = F_LEFT;
        if (!isTileSolid(player.x - 1, player.y)) {
            move(F_LEFT);
        }
        //renderPlayer();
    } else if (KEYPRESSED(J_RIGHT)) {
        playerFacing = F_RIGHT;
        if (!isTileSolid(player.x + 1, player.y)) {
            move(F_RIGHT);
        }
        //renderPlayer();
    }
}

void move(Facing direction) {
    if (direction == F_UP) {
        player.y--;

        renderedMap.top--;
        renderedMap.bottom--;
        if (viewport.top == 0)      viewport.top = META_TILEMAP_HEIGHT - 1;
        else                        viewport.top--;
        if (viewport.bottom == 0)   viewport.bottom = META_TILEMAP_HEIGHT - 1;
        else                        viewport.bottom--;
        renderRow(viewport.left, viewport.top, renderedMap.left, renderedMap.top);
    } else if (direction == F_DOWN) {
        player.y++;

        renderedMap.top++;
        renderedMap.bottom++;
        if (viewport.top == META_TILEMAP_HEIGHT - 1)    viewport.top = 0;
        else                                            viewport.top++;
        if (viewport.bottom == META_TILEMAP_HEIGHT - 1) viewport.bottom = 0;
        else                                            viewport.bottom++;
        renderRow(viewport.left, viewport.bottom, renderedMap.left, renderedMap.bottom);
    } else if (direction == F_LEFT) {
        player.x--;

        renderedMap.left--;
        renderedMap.right--;
        if (viewport.left == 0)     viewport.left = META_TILEMAP_WIDTH - 1;
        else                        viewport.left--;
        if (viewport.right == 0)    viewport.right = META_TILEMAP_WIDTH - 1;
        else                        viewport.right--;
        renderColumn(viewport.left, viewport.top, renderedMap.left, renderedMap.top);
    } else if (direction == F_RIGHT) {
        player.x++;

        renderedMap.left++;
        renderedMap.right++;
        if (viewport.left == META_TILEMAP_WIDTH - 1)    viewport.left = 0;
        else                                            viewport.left++;
        if (viewport.right == META_TILEMAP_WIDTH - 1)   viewport.right = 0;
        else                                            viewport.right++;
        renderColumn(viewport.right, viewport.top, renderedMap.right, renderedMap.top);
    }
    move_bkg(viewport.left * 16, viewport.top * 16);
    //updateCamera();
}

void updateCamera() {
    Point old = {.x = metaCamera.x, .y = metaCamera.y};

    if (player.x < 5)
        metaCamera.x = 0;
    else
        metaCamera.x = player.x - 5;
    if (player.y < 4)
        metaCamera.y = 0;
    else
        metaCamera.y = player.y - 4;

    //scroll_bkg((metaCamera.x - old.x) * 16, (metaCamera.y - old.y) * 16);

    // Load in more of the tilemap as necessary
    // TODO: Need to check viewport edges against RELATIVE camera position, not metacamera
    //if (metaCamera.x < viewportEdgeLeft) {
    //    renderColumn(viewportEdgeLeft, viewportEdgeTop, metaCamera.x, metaCamera.y);
    //    viewportEdgeLeft = metaCamera.x;
    //}
    //if (metaCamera.x + META_SCREEN_WIDTH > viewportEdgeRight) {
    //    renderColumn(viewportEdgeRight, viewportEdgeTop, metaCamera.x, metaCamera.y);
    //    viewportEdgeRight = metaCamera.x + META_SCREEN_WIDTH;
    //}
    //if (metaCamera.y < viewportEdgeTop) {
    //    renderRow(viewportEdgeLeft, viewportEdgeTop, metaCamera.x, metaCamera.y);
    //    viewportEdgeTop = metaCamera.y;
    //}
    //if (metaCamera.y + META_SCREEN_HEIGHT > viewportEdgeBottom) {
    //    renderRow(viewportEdgeLeft, viewportEdgeBottom, metaCamera.x, metaCamera.y);
    //    viewportEdgeBottom = metaCamera.y + META_SCREEN_HEIGHT;
    //}
}

inline uint8_t getMetaTile(uint8_t x, uint8_t y) {
    if (x >= METAMAP_WIDTH || y >= METAMAP_HEIGHT) return 0;
    return metamap_map[x + y * METAMAP_WIDTH];
}

inline uint8_t isTileSolid(uint8_t x, uint8_t y) {
    return getMetaTile(x, y) != 2;
}

inline void renderPlayer() {
    uint8_t frameId = 0;
    if (playerFacing == F_UP) frameId = 3;
    else if (playerFacing == F_LEFT || playerFacing == F_RIGHT) frameId = 6;

    uint8_t x = (player.x/* - metaCamera.x*/) * 16 + 16;
    uint8_t y = (player.y/* - metaCamera.y*/) * 16 + 24;

    if (playerFacing == F_LEFT)
        move_metasprite_vflip(zymie_metasprites[frameId], zymieBaseTile, zymieBaseSprite, x, y);
    else
        move_metasprite(zymie_metasprites[frameId], zymieBaseTile, zymieBaseSprite, x, y);
}

inline void renderMetatile(uint8_t x, uint8_t y, uint8_t tileId) {
    set_bkg_tile_xy(x * 2, y * 2, tileId * 4 + tilesBase);
    set_bkg_tile_xy(x * 2 + 1, y * 2, tileId * 4 + tilesBase + 1);
    set_bkg_tile_xy(x * 2, y * 2 + 1, tileId * 4 + tilesBase + 2);
    set_bkg_tile_xy(x * 2 + 1, y * 2 + 1, tileId * 4 + tilesBase + 3);
}

inline void renderColumn(uint8_t xFrom, uint8_t yFrom, uint8_t bx, uint8_t by) {
    for (uint8_t y = 0; y < META_SCREEN_HEIGHT; y++) {
        renderMetatile(xFrom, (y + yFrom) % 16, getMetaTile(bx, y + by));
    }
}

inline void renderRow(uint8_t xFrom, uint8_t yFrom, uint8_t bx, uint8_t by) {
    for (uint8_t x = 0; x < META_SCREEN_WIDTH; x++) {
        renderMetatile((x + xFrom) % 16, yFrom, getMetaTile(x + bx, by));
    }
}

// TODO: Should probably rename this function since it is only intended to be used for an initial render
inline void renderMetamap(uint8_t bx, uint8_t by) {
    for (uint8_t x = 0; x < META_SCREEN_WIDTH; x++) {
        for (uint8_t y = 0; y < META_SCREEN_HEIGHT; y++) {
            renderMetatile(x, y, getMetaTile(x + bx, y + by));
        }
    }
}

