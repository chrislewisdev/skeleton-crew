#ifndef CORE_H
#define CORE_H

#include <gb/gb.h>

#define NULL    0

#define KEYPRESSED(KEY) ((input & KEY) && !(previousInput & KEY))

typedef enum AppState {
    STATE_SPLASH,
    STATE_TITLE,
    STATE_INTRO,
    STATE_EXPLORE,
    STATE_BATTLE,
    STATE_OUTRO,
    STATE_CREDITS
} AppState;

extern AppState appState;
extern void (*currentStateCleanup)();

extern uint8_t input, previousInput;
extern uint8_t gfxTileOffset, objTileOffset, spriteOffset;

void switchToState(AppState targetState);

inline uint8_t claimBkgGfx(uint8_t numTiles, const uint8_t *data);
inline uint8_t claimBkgGfxRaw(uint8_t numTiles);
inline void releaseAllBkgGfx();
inline uint8_t claimObjGfx(uint8_t numTiles, const uint8_t *data);
inline void releaseAllObjGfx();
inline uint8_t claimSprite();
inline uint8_t claimSprites(uint8_t numSprites);
inline void releaseAllSprites();

#endif

