#ifndef BATTLE_H
#define BATTLE_H

#include <gb/gb.h>

typedef enum BattleOutcome {
    OUTCOME_VICTORY,
    OUTCOME_DEFEAT,
    OUTCOME_ESCAPED,
} BattleOutcome;

extern uint8_t triggerBossBattle;
extern uint8_t xpGained;
extern BattleOutcome battleOutcome;

void stateInitBattle();
void stateUpdateBattle();
void stateCleanupBattle();

#endif

