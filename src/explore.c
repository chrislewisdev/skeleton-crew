#pragma bank 1

#include "explore.h"
#include "core.h"
#include "hUGEDriver.h"
#include "battle.h"
#include "transition.h"
#include "ui.h"
#include "vwf.h"
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

#define BASE_ENCOUNTER_CHANCE 15

typedef struct Bounds { uint8_t left, right, top, bottom; } Bounds;

typedef enum Facing { F_UP, F_DOWN, F_LEFT, F_RIGHT } Facing;

BANKREF_EXTERN(dungeon_stroll)
extern const hUGESong_t dungeon_stroll;

uint8_t tilesBase;
uint8_t zymieBaseTile, zymieBaseSprite;
Point player = {.x = 8, .y = 7};
Point metaCamera = {.x = 0, .y = 2};
Bounds viewport = {.left = 0, .right = META_SCREEN_WIDTH, .top = 0, .bottom = META_SCREEN_HEIGHT};
Bounds renderedMap = {.left = 0, .right = META_SCREEN_WIDTH, .top = 0, .bottom = META_SCREEN_HEIGHT};
Facing playerFacing = F_DOWN;
uint8_t stepCounter;
uint8_t isMoving = FALSE;
uint8_t playerAnimationFrame = 0, stepAnimationAlternator = 0;
uint8_t encounterChance;

inline void renderMetamap(uint8_t, uint8_t);
inline void renderColumn(uint8_t, uint8_t, uint8_t, uint8_t);
inline void renderRow(uint8_t, uint8_t, uint8_t, uint8_t);
inline void renderPlayer();
inline uint8_t isTileSolid(uint8_t, uint8_t);
void updateCamera();
void move(Facing direction);
inline uint8_t getMetaTile(uint8_t, uint8_t);

void stateInitExplore() {
    HIDE_BKG;
    HIDE_SPRITES;
    hide_sprites_range(0, MAX_HARDWARE_SPRITES);

    releaseAllBkgGfx();
    releaseAllObjGfx();
    releaseAllSharedGfx();
    releaseAllSprites();

    initUi();
    tilesBase = claimBkgGfx(tiles_TILE_COUNT, tiles_tiles);
    zymieBaseTile = claimObjGfx(zymie_TILE_COUNT, zymie_tiles);
    zymieBaseSprite = claimSprites(4);

    renderPlayer();
    renderedMap.left = player.x - 5;
    renderedMap.right = renderedMap.left + META_SCREEN_WIDTH;
    renderedMap.top = player.y - 4;
    renderedMap.bottom = renderedMap.top + META_SCREEN_HEIGHT;
    renderMetamap(renderedMap.left, renderedMap.top);
    move_bkg(8, 8);

    viewport.left = 0; viewport.right = META_SCREEN_WIDTH;
    viewport.top = 0; viewport.bottom = META_SCREEN_HEIGHT;

    startMusic(&dungeon_stroll, BANK(dungeon_stroll));
    
    SHOW_BKG;
    SHOW_SPRITES;

    stepCounter = 0;
    encounterChance = BASE_ENCOUNTER_CHANCE;
}

inline uint8_t getFacedTile() {
    uint8_t x = player.x, y = player.y;
    if (playerFacing == F_UP) {
        y -= 1;
    } else if (playerFacing == F_DOWN) {
        y += 1;
    } else if (playerFacing == F_LEFT) {
        x -= 1;
    } else if (playerFacing == F_RIGHT) {
        x += 1;
    }
    return getMetaTile(x, y);
}

void tryInteract(uint8_t tileId) {
    if (tileId == 3) {
        queueStateSwitch(STATE_FOUNTAIN);
    }
}

void stateUpdateExplore() {
    if (KEYDOWN(J_UP) && !isMoving) {
        playerFacing = F_UP;
        if (!isTileSolid(player.x, player.y - 1)) {
            move(F_UP);
        }
        renderPlayer();
    } else if (KEYDOWN(J_DOWN) && !isMoving) {
        playerFacing = F_DOWN;
        if (!isTileSolid(player.x, player.y + 1)) {
            move(F_DOWN);
        }
        renderPlayer();
    } else if (KEYDOWN(J_LEFT) && !isMoving) {
        playerFacing = F_LEFT;
        if (!isTileSolid(player.x - 1, player.y)) {
            move(F_LEFT);
        }
        renderPlayer();
    } else if (KEYDOWN(J_RIGHT) && !isMoving) {
        playerFacing = F_RIGHT;
        if (!isTileSolid(player.x + 1, player.y)) {
            move(F_RIGHT);
        }
        renderPlayer();
    } else if (KEYDOWN(J_A)) {
        uint8_t tileId = getFacedTile();
        tryInteract(tileId);
    }
}

uint8_t checkRandomEncounter() {
    encounterChance--;
    if (rand() % encounterChance == 0)  return 1;
    else                                return 0;
}

uint8_t sfSmoothScroll(uint8_t step) {
    if (step < 16 && step % 2 == 0) {
        if (playerFacing == F_UP) {
            scroll_bkg(0, -2);
        } else if (playerFacing == F_DOWN) {
            scroll_bkg(0, 2);
        } else if (playerFacing == F_LEFT) {
            scroll_bkg(-2, 0);
        } else if (playerFacing == F_RIGHT) {
            scroll_bkg(2, 0);
        }
    }

    // Trigger animation frames
    playerAnimationFrame = step > 8 ? 0 : stepAnimationAlternator + 1;
    renderPlayer();

    if (step >= 19) {
        // Trigger 'end-of-step' logic
        isMoving = FALSE;
        playerAnimationFrame = 0;
        renderPlayer();
        stepCounter++;
        if (getMetaTile(player.x, player.y) == 5) {
            triggerBossBattle = TRUE;
            transitionTarget = STATE_BATTLE;
            queueStateSwitch(STATE_TRANSITION);
        } else if (stepCounter >= 5 && checkRandomEncounter()) {
            encounterChance = BASE_ENCOUNTER_CHANCE;
            triggerBossBattle = FALSE;
            transitionTarget = STATE_BATTLE;
            queueStateSwitch(STATE_TRANSITION);
        }
        return 1;
    } else {
        return 0;
    }
}

void move(Facing direction) {
    // TODO: We can probably clean up this code using % META_TILEMAP_HEIGHT instead of all these checks
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
    //move_bkg(viewport.left * 16 + 8, viewport.top * 16 + 8);
    startStepFunction(sfSmoothScroll);
    isMoving = TRUE;
    stepAnimationAlternator = (stepAnimationAlternator + 1) % 2;
}

inline uint8_t getMetaTile(uint8_t x, uint8_t y) {
    if (x >= METAMAP_WIDTH || y >= METAMAP_HEIGHT) return 0;
    return metamap_map[x + y * METAMAP_WIDTH];
}

inline uint8_t isTileSolid(uint8_t x, uint8_t y) {
    uint8_t metatile = getMetaTile(x, y);
    return metatile != 2 && metatile != 5;
}

inline void renderPlayer() {
    uint8_t frameId = playerAnimationFrame;
    if (playerFacing == F_UP) frameId += 3;
    else if (playerFacing == F_LEFT || playerFacing == F_RIGHT) frameId += 6;

    uint8_t x = 5 * 16 + 8;
    uint8_t y = 4 * 16 + 16;

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
    for (uint8_t y = 0; y <= META_SCREEN_HEIGHT; y++) {
        renderMetatile(xFrom, (y + yFrom) % 16, getMetaTile(bx, y + by));
    }
}

inline void renderRow(uint8_t xFrom, uint8_t yFrom, uint8_t bx, uint8_t by) {
    for (uint8_t x = 0; x <= META_SCREEN_WIDTH; x++) {
        renderMetatile((x + xFrom) % 16, yFrom, getMetaTile(x + bx, by));
    }
}

// TODO: Should probably rename this function since it is only intended to be used for an initial render
inline void renderMetamap(uint8_t bx, uint8_t by) {
    for (uint8_t x = 0; x <= META_SCREEN_WIDTH; x++) {
        for (uint8_t y = 0; y <= META_SCREEN_HEIGHT; y++) {
            renderMetatile(x, y, getMetaTile(x + bx, y + by));
        }
    }
}

