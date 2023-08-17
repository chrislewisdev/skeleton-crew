#include "core.h"
#include "rpg.h"

const Skill skills[7] = {
    {.id = 0, .name = "Fireball"},
    {.id = 1, .name = "Gust"},
    {.id = 2, .name = "Rain"},
    {.id = 3, .name = "Heal"},
    {.id = 4, .name = "Blast"},
    {.id = 5, .name = "Cyclone"},
    {.id = 6, .name = "Downpour"},
};

Character party[4];

inline uint8_t calculateDmg(Character* target, Character* origin, uint8_t basePower, Element element) {
    uint8_t base = basePower + (element == PHYSICAL ? origin->atk : origin->spAtk);

    uint8_t withAffinity = base;
    if (target->affinities[element] == WEAK) {
        withAffinity = base + (base / 2);
    } else if (target->affinities[element] == RESIST) {
        withAffinity = base / 2;
    }

    return (element == PHYSICAL ? withAffinity - target->def : withAffinity - target->spDef);
}

