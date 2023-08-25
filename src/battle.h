#ifndef BATTLE_H
#define BATTLE_H

#include <gb/gb.h>

extern uint8_t triggerBossBattle;
extern uint8_t xpGained;

void stateInitBattle();
void stateUpdateBattle();
void stateCleanupBattle();

#endif

