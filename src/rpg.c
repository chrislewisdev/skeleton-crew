#include "core.h"
#include "rpg.h"
#include "gen/zombie.h"
#include "gen/slime.h"

#define NONE  {0}
#define ENEMY(NAME, HP, ATK, DEF, SPATK, SPDEF, AFF, SKILLS, META, TILECOUNT, TILES) \
    {.name=NAME, .hp=HP, .atk=ATK, .def=DEF, .spAtk=SPATK, .spDef=SPDEF,\
        .affinities=AFF, .skills=SKILLS,\
        .metasprite=META, .tileCount=TILECOUNT, .tiles=TILES, .baseTile=0}

const Skill skills[7] = {
    {.id = 0, .name = "Fireball"},
    {.id = 1, .name = "Gust"},
    {.id = 2, .name = "Rain"},
    {.id = 3, .name = "Heal"},
    {.id = 4, .name = "Blast"},
    {.id = 6, .name = "Downpour"},
    {.id = 5, .name = "Cyclone"},
};

extern const metasprite_t zombie_metasprite0;
extern const metasprite_t slime_metasprite0;
EnemyType enemyTypes[ENEMY_TYPE_COUNT] = {
    ENEMY("Slime", 10, 2, 2, 1, 1, NONE, NONE, &zombie_metasprite0, slime_TILE_COUNT, slime_tiles),
    ENEMY("Zombie", 7, 3, 1, 1, 0, NONE, NONE, &slime_metasprite0, zombie_TILE_COUNT, zombie_tiles),
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

