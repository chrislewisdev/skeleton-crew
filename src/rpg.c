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
#define WEAK2FIRE {NORMAL, WEAK, NORMAL, NORMAL}
#define WEAK2WIND {NORMAL, NORMAL, WEAK, NORMAL}
#define WEAK2WATER {NORMAL, NORMAL, NORMAL, WEAK}
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

void applyWeaken(Character* target) {
    if (target->atk > 3) target->atk -= 3;
}
void applySoften(Character* target) {
    if (target->def > 3) target->def -= 3;
    // SpDef?
}
void applyHeal(Character* target) {
    target->hp += 20;
    if (target->hp > target->maxHp) target->hp = target->maxHp;
}

const Skill skills[SKILL_TYPE_COUNT] = {
    {.id = 0, .name = ""}, //Empty skill
    {.id = 1, .name = "Fireball", .element = FIRE, .power = 5, .effect = NULL},
    {.id = 2, .name = "Gust", .element = WIND, .power = 5, .effect = NULL},
    {.id = 3, .name = "Rain", .element = WATER, .power = 5, .effect = NULL},
    {.id = 4, .name = "Heal", .effect = applyHeal},
    {.id = 5, .name = "Fireblast", .element = FIRE, .power = 10, .effect = NULL},
    {.id = 6, .name = "Cyclone", .element = WIND, .power = 10, .effect = NULL},
    {.id = 7, .name = "Downpour", .element = WATER, .power = 10, .effect = NULL},
    {.id = 8, .name = "Mega Punch", .element = PHYSICAL, .power = 10, .effect = NULL},
    {.id = 9, .name = "Weaken", .effect = applyWeaken},
    {.id = 10, .name = "Soften", .effect = applySoften},
    {.id = 11, .name = "Slam", .element = PHYSICAL, .power = 5, .effect = NULL}
};

extern const metasprite_t zombie_metasprite0;
extern const metasprite_t slime_metasprite0;
extern const metasprite_t harpy_metasprite0;
extern const metasprite_t skull_metasprite0;
extern const metasprite_t ghost_metasprite0;
extern const metasprite_t spider_metasprite0;
extern const metasprite_t boss_metasprite0;
EnemyType enemyTypes[ENEMY_TYPE_COUNT] = {
    ENEMY("Slime", 8, 3, 2, 1, 1, WEAK2WIND, NONE, 3, &zombie_metasprite0, slime_TILE_COUNT, slime_tiles),
    ENEMY("Zombie", 15, 4, 1, 1, 0, WEAK2FIRE, NONE, 3, &slime_metasprite0, zombie_TILE_COUNT, zombie_tiles),
    ENEMY("Spider", 25, 9, 4, 1, 4, WEAK2FIRE, NONE, 6, &spider_metasprite0, spider_TILE_COUNT, spider_tiles),
    ENEMY("Skull", 32, 8, 3, 1, 10, WEAK2WATER, NONE, 8, &skull_metasprite0, skull_TILE_COUNT, skull_tiles),
    ENEMY("Ghost", 30, 12, 99, 1, 3, WEAK2WIND, NONE, 20, &ghost_metasprite0, ghost_TILE_COUNT, ghost_tiles),
    ENEMY("Harpy", 50, 15, 8, 1, 10, WEAK2WATER, NONE, 24, &harpy_metasprite0, harpy_TILE_COUNT, harpy_tiles),
    ENEMY("Demon", 150, 20, 20, 20, 20, NONE, NONE, 0, &boss_metasprite0, boss_TILE_COUNT, boss_tiles),
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
        .learnedSkills = {LEARN(3, 2), LEARN(7, 4), LEARN(10, 6), NOSKILL}, // Gust, Heal, Cyclone
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
        .learnedSkills = {LEARN(5, 3), LEARN(9, 7), LEARN(12, 10), NOSKILL}, // Rain, Downpour, Soften
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
        .learnedSkills = {LEARN(2, 1), LEARN(4, 9), LEARN(8, 5), NOSKILL},  // Fireball, Weaken, Fireblast
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
        .learnedSkills = {LEARN(6, 11), LEARN(11, 8), NOSKILL, NOSKILL}, // Roundhouse, Mega Punch
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
    c->atk = 4 + c->lvl;
    c->def = 5 + c->lvl;
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
    c->spAtk = 3 + c->lvl * 2;
    c->spDef = 5 + c->lvl * 2;
}
void applyPierreGrowths(Character* c) {
    c->maxHp = 10 + c->lvl * 3;
    c->hp = c->maxHp;
    c->atk = 2 + c->lvl * 2;
    c->def = 2 + c->lvl;
    c->spAtk = 2 + c->lvl * 2;
    c->spDef = 2 + c->lvl;
}

