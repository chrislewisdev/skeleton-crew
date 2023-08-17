#include "core.h"
#include "rpg.h"

inline uint8_t calculateDmg(Character* target, Character* origin, uint8_t basePower, Element element) {
    uint8_t base = basePower + (element == PHYSICAL ? origin->atk : origin->spAtk);

    uint8_t withAffinity;
    if (target->affinities[element] == WEAK) {
        withAffinity = base + (base / 2);
    } else if (target->affinities[element] == RESIST) {
        withAffinity = base / 2;
    }

    return (element == PHYSICAL ? withAffinity - target->def : withAffinity - target->spDef);
}

