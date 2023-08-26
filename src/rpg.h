#ifndef RPG_H
#define RPG_H

#include <gb/gb.h>
#include <gb/metasprites.h>

#define ENEMY_TYPE_COUNT    7
#define SKILL_TYPE_COUNT    11

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

typedef struct LearnedSkill {
    uint8_t lvlRequired, skillId;
} LearnedSkill;

typedef struct Character {
    const char* name;
    uint8_t isAlly;
    uint8_t lvl, xp;
    uint8_t hp, maxHp;
    uint8_t atk, def;
    uint8_t spAtk, spDef;
    uint8_t affinities[4];
    uint8_t skills[4];
    LearnedSkill learnedSkills[4];
    void (*growthFunction)(struct Character*);
} Character;

typedef struct EnemyType {
    const char* name;
    uint8_t hp;
    uint8_t atk, def;
    uint8_t spAtk, spDef;
    uint8_t affinities[4];
    uint8_t skills[4];
    uint8_t xp;
    const metasprite_t* metasprite;
    uint8_t tileCount;
    const uint8_t* tiles;
    uint8_t baseTile;
} EnemyType;

typedef struct Skill {
    uint8_t id;
    const char* name;
    //void (*effect)();
} Skill;

inline uint8_t calculateDmg(Character* target, Character* origin, uint8_t basePower, Element element);
uint8_t awardXp(Character* c, uint8_t xp);

extern const Skill skills[SKILL_TYPE_COUNT];
extern Character party[4];
extern EnemyType enemyTypes[ENEMY_TYPE_COUNT];

#endif

