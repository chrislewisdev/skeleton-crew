#ifndef CORE_H
#define CORE_H

#include <gb/gb.h>

#define NULL    0

typedef enum AppState {
    STATE_SPLASH,
    STATE_TITLE,
    STATE_INTRO,
    STATE_EXPLORE,
    STATE_BATTLE,
    STATE_OUTRO,
} AppState;

extern AppState appState;
extern void (*currentStateCleanup)();

void switchToState(AppState targetState);

inline uint8_t claimBkgGfx(uint8_t numTiles, const uint8_t* data);
inline void releaseAllBkgGfx();

#endif

