#ifndef EXPLORE_H
#define EXPLORE_H

#include <gb/gb.h>

typedef struct Point { uint8_t x; uint8_t y; } Point;

extern Point player;

void stateInitExplore();
void stateUpdateExplore();

#endif
