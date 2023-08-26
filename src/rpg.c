#include "core.h"
#include "rpg.h"
#include "gen/zombie.h"
#include "gen/slime.h"
#include "gen/spider.h"
#include "gen/harpy.h"
#include "gen/skull.h"
#include "gen/ghost.h"
#include "gen/boss.h"

#define NONE  {0}
#define ENEMY(NAME, HP, ATK, DEF, SPATK, SPDEF, AFF, SKILLS, XP, META, TILECOUNT, TILES) \
    {.name=NAME, .hp=HP, .atk=ATK, .def=DEF, .spAtk=SPATK, .spDef=SPDEF,\
        .affinities=AFF, .skills=SKILLS, .xp=XP,\
        .metasprite=META, .tileCount=TILECOUNT, .tiles=TILES, .baseTile=0}
#define LEARN(LVL, SKILLID) {.lvlRequired=LVL, .skillId=SKILLID}
#define NOSKILL LEARN(0, 0)

void applyZymieGrowths(Character*);
void applyIvanGrowths(Character*);
void applyOlafGrowths(Character*);
void applyPierreGrowths(Character*);

const Skill skills[SKILL_TYPE_COUNT] = {
    {.id = 0, .name = "Fireball"},
    {.id = 1, .name = "Gust"},
    {.id = 2, .name = "Rain"},
    {.id = 3, .name = "Heal"},
    {.id = 4, .name = "Blast"},
    {.id = 5, .name = "Cyclone"},
    {.id = 6, .name = "Downpour"},
    {.id = 7, .name = "Mega Punch"},
    {.id = 8, .name = "Weaken"},
    {.id = 9, .name = "Soften"},
    {.id = 10, .name = "Fast Kick"}
};

extern const metasprite_t zombie_metasprite0;
extern const metasprite_t slime_metasprite0;
extern const metasprite_t harpy_metasprite0;
extern const metasprite_t skull_metasprite0;
extern const metasprite_t ghost_metasprite0;
extern const metasprite_t spider_metasprite0;
extern const metasprite_t boss_metasprite0;
EnemyType enemyTypes[ENEMY_TYPE_COUNT] = {
    ENEMY("Slime", 10, 2, 2, 1, 1, NONE, NONE, 1, &zombie_metasprite0, slime_TILE_COUNT, slime_tiles),
    ENEMY("Zombie", 7, 3, 1, 1, 0, NONE, NONE, 1, &slime_metasprite0, zombie_TILE_COUNT, zombie_tiles),
    ENEMY("Harpy", 7, 3, 1, 1, 0, NONE, NONE, 5, &harpy_metasprite0, harpy_TILE_COUNT, harpy_tiles),
    ENEMY("Skull", 7, 3, 1, 1, 0, NONE, NONE, 4, &skull_metasprite0, skull_TILE_COUNT, skull_tiles),
    ENEMY("Ghost", 7, 3, 1, 1, 0, NONE, NONE, 3, &ghost_metasprite0, ghost_TILE_COUNT, ghost_tiles),
    ENEMY("Spider", 7, 3, 1, 1, 0, NONE, NONE, 3, &spider_metasprite0, spider_TILE_COUNT, spider_tiles),
    ENEMY("Demon", 15, 5, 3, 3, 3, NONE, NONE, 0, &boss_metasprite0, boss_TILE_COUNT, boss_tiles),
};

Character party[4] = {
    {
        .name = "Zymie",
        .isAlly = TRUE,
        .lvl = 1, .xp = 0,
        .hp = 35, .maxHp = 35,
        .atk = 1, .def = 1,
        .spAtk = 1, .spDef = 1,
        .affinities = NONE,
        .skills = NONE,
        .learnedSkills = {NOSKILL, NOSKILL, NOSKILL, NOSKILL},
        .growthFunction = applyZymieGrowths,
    },
    {
        .name = "Ivan",
        .isAlly = TRUE,
        .lvl = 1, .xp = 0,
        .hp = 35, .maxHp = 35,
        .atk = 1, .def = 1,
        .spAtk = 1, .spDef = 1,
        .affinities = NONE,
        .skills = NONE,
        .learnedSkills = {NOSKILL, NOSKILL, NOSKILL, NOSKILL},
        .growthFunction = applyIvanGrowths,
    },
    {
        .name = "Olaf",
        .isAlly = TRUE,
        .lvl = 1, .xp = 0,
        .hp = 35, .maxHp = 35,
        .atk = 1, .def = 1,
        .spAtk = 1, .spDef = 1,
        .affinities = NONE,
        .skills = NONE,
        .learnedSkills = {LEARN(2, 4), NOSKILL, NOSKILL, NOSKILL},
        .growthFunction = applyOlafGrowths,
    },
    {
        .name = "Pierre",
        .isAlly = TRUE,
        .lvl = 1, .xp = 0,
        .hp = 35, .maxHp = 35,
        .atk = 1, .def = 1,
        .spAtk = 1, .spDef = 1,
        .affinities = NONE,
        .skills = NONE,
        .learnedSkills = {NOSKILL, NOSKILL, NOSKILL, NOSKILL},
        .growthFunction = applyPierreGrowths,
    }
};

inline uint8_t calculateDmg(Character* target, Character* origin, uint8_t basePower, Element element) {
    uint8_t base = basePower + (element == PHYSICAL ? origin->atk : origin->spAtk);

    uint8_t withAffinity = base;
    if (target->affinities[element] == WEAK) {
        withAffinity = base + (base / 2);
    } else if (target->affinities[element] == RESIST) {
        withAffinity = base / 2;
    }

    if (element == PHYSICAL) {
        return target->def >= withAffinity ? 1 : withAffinity - target->def;
    } else {
        return target->spDef >= withAffinity ? 1 : withAffinity - target->spDef;
    }
}

inline uint8_t getRequiredXp(uint8_t level) {
    return level * 10;
}

uint8_t awardXp(Character* c, uint8_t xp) {
    uint8_t xpForLevelUp = getRequiredXp(c->lvl);
    c->xp += xp;

    if (c->xp < xpForLevelUp) return 0;

    c->lvl++;
    c->xp -= xpForLevelUp;
    c->growthFunction(c);

    for (uint8_t i = 0; i < 4; i++) {
        if (c->learnedSkills[i].lvlRequired > 0 && c->lvl >= c->learnedSkills[i].lvlRequired) {
            c->skills[i] = c->learnedSkills[i].skillId;
        }
    }

    return 1;
}

void applyZymieGrowths(Character* c) {
    c->maxHp = 7 + c->lvl * 3;
    c->hp = c->maxHp;
    c->atk = 2 + c->lvl;
    c->def = 2 + c->lvl;
    c->spAtk = 2 + c->lvl;
    c->spDef = 2 + c->lvl;
}
void applyIvanGrowths(Character* c) {
    c->maxHp = 8 + c->lvl * 4;
    c->hp = c->maxHp;
    c->atk = 2 + c->lvl;
    c->def = 3 + c->lvl * 2;
    c->spAtk = 2 + c->lvl;
    c->spDef = 4 + (c->lvl / 2);
}
void applyOlafGrowths(Character* c) {
    c->maxHp = 5 + c->lvl * 2;
    c->hp = c->maxHp;
    c->atk = 1 + c->lvl;
    c->def = 2 + c->lvl;
    c->spAtk = 3 + c->lvl * 3;
    c->spDef = 5 + c->lvl * 2;
}
void applyPierreGrowths(Character* c) {
    c->maxHp = 10 + c->lvl * 3;
    c->hp = c->maxHp;
    c->atk = 2 + c->lvl * 3;
    c->def = 2 + c->lvl;
    c->spAtk = 2 + c->lvl * 2;
    c->spDef = 2 + c->lvl;
}

