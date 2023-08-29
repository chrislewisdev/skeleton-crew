#include <string.h>
#include "core.h"
#include "rpg.h"
#include "explore.h"

const char memoryTestString[] = "String for testing RAM init";

char initString[sizeof(memoryTestString)];
uint8_t partyLvl[4];
uint8_t x, y;

uint8_t hasSaveData() {
    return memcmp(initString, memoryTestString, sizeof(memoryTestString)) == 0 ? TRUE : FALSE;
} 

void saveData() {
    ENABLE_RAM_MBC5;
    if (!hasSaveData()) {
        memcpy(initString, memoryTestString, sizeof(memoryTestString));
    }
    for (uint8_t i = 0; i < 4; i++) {
        partyLvl[i] = party[i].lvl;
    }
    x = player.x;
    y = player.y;
    DISABLE_RAM_MBC5;
}

void loadData() {
    ENABLE_RAM_MBC5;
    for (uint8_t i = 0; i < 4; i++) {
        party[i].lvl = partyLvl[i];
    }
    player.x = x;
    player.y = y;
    applyLvlsToParty();
    DISABLE_RAM_MBC5;
}

