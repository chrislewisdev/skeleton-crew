#ifndef CORE_H
#define CORE_H

#include <gb/gb.h>
#include "hUGEDriver.h"

#define NULL    0

#define KEYPRESSED(KEY) ((input & KEY) && !(previousInput & KEY))
#define KEYDOWN(KEY)    (input & KEY)

typedef enum AppState {
    STATE_NONE,
    STATE_SPLASH,
    STATE_TITLE,
    STATE_INTRO,
    STATE_EXPLORE,
    STATE_BATTLE,
    STATE_OUTRO,
    STATE_CREDITS,
    STATE_TRANSITION,
    STATE_POSTBATTLE,
} AppState;

extern AppState appState;
extern void (*currentStateUpdate)();
extern void (*currentStateCleanup)();

extern uint8_t input, previousInput;
extern uint8_t gfxTileOffset, objTileOffset, spriteOffset, sharedTileOffset;
extern uint8_t playMusic, musicBank;

void queueStateSwitch(AppState targetState);
void checkStateSwitch();

inline void startMusic(hUGESong_t* song, uint8_t bank);
inline void stopMusic();

inline uint8_t claimBkgGfx(uint8_t numTiles, const uint8_t *data);
inline uint8_t claimBkgGfxRaw(uint8_t numTiles);
inline void releaseAllBkgGfx();
inline uint8_t claimObjGfx(uint8_t numTiles, const uint8_t *data);
inline void releaseAllObjGfx();
inline uint8_t claimSharedGfx(uint8_t numTiles, const uint8_t *data);
inline void releaseAllSharedGfx();
inline uint8_t claimSprite();
inline uint8_t claimSprites(uint8_t numSprites);
inline void releaseAllSprites();

inline void startStepFunction(uint8_t (*function)(uint8_t));
inline void runStepFunctions();

#endif

