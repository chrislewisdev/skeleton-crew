#ifndef RPG_H
#define RPG_H

#include <gb/gb.h>
#include <gb/metasprites.h>

typedef enum Element {
    PHYSICAL,
    FIRE,
    WIND,
    WATER,
} Element;

typedef enum Affinity {
    NORMAL,
    WEAK,
    RESIST,
} Affinity;

typedef struct Character {
    uint8_t lvl, xp;
    uint8_t hp, maxHp;
    uint8_t atk, def;
    uint8_t spAtk, spDef;
    uint8_t affinities[4];
    uint8_t skills[4];
    metasprite_t *metasprite;
} Character;

typedef struct Skill {
    uint8_t id;
    const char* name;
    //void (*effect)();
} Skill;

inline uint8_t calculateDmg(Character* target, Character* origin, uint8_t basePower, Element element);

Skill skills[] = {
    {.id = 0, .name = "Fireball"},
    {.id = 1, .name = "Gust"},
    {.id = 2, .name = "Rain"},
    {.id = 3, .name = "Heal"},
    {.id = 4, .name = "Blast"},
    {.id = 5, .name = "Cyclone"},
    {.id = 6, .name = "Downpour"},
};

#endif

