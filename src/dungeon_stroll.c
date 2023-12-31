#pragma bank 2

#include "hUGEDriver.h"
#include <stddef.h>

BANKREF(dungeon_stroll)

static const unsigned char order_cnt = 18;

static const unsigned char P0[] = {
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Ds5,7,0x000),
    DN(___,0,0x000),
    DN(Ds5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(As5,7,0x000),
    DN(___,0,0x000),
    DN(As5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P1[] = {
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_4,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xD01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P2[] = {
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P4[] = {
    DN(Cs5,7,0x8FF),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(E_5,7,0x000),
    DN(___,0,0x000),
    DN(Ds5,7,0x000),
    DN(Cs5,7,0x000),
    DN(Ds5,7,0x000),
    DN(___,0,0x000),
    DN(B_4,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(As5,7,0x000),
    DN(B_5,7,0x000),
    DN(As5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xD01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P5[] = {
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Fs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(As4,9,0x000),
    DN(___,0,0x000),
    DN(Fs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P6[] = {
    DN(___,0,0xC00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P7[] = {
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P8[] = {
    DN(Fs6,7,0x022),
    DN(___,0,0x022),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(Fs6,7,0x000),
    DN(E_6,7,0x000),
    DN(Fs6,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC00),
    DN(___,0,0x000),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(Ds6,7,0x011),
    DN(___,0,0x011),
    DN(Ds6,7,0x000),
    DN(___,0,0xC00),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(B_5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC00),
    DN(___,0,0x000),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(Fs6,7,0x022),
    DN(___,0,0x022),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(Fs6,7,0x000),
    DN(E_6,7,0x000),
    DN(Fs6,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC00),
    DN(___,0,0x000),
    DN(Cs6,7,0x000),
    DN(___,0,0xC00),
    DN(Gs6,7,0x000),
    DN(___,0,0x000),
    DN(As6,7,0x000),
    DN(___,0,0xC00),
    DN(B_6,7,0x000),
    DN(___,0,0xC00),
    DN(As6,7,0x000),
    DN(___,0,0xC00),
    DN(Gs6,7,0x000),
    DN(___,0,0x000),
    DN(Fs6,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P9[] = {
    DN(Gs6,7,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(Fs6,7,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(E_6,7,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(D_6,7,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
};
static const unsigned char P10[] = {
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P11[] = {
    DN(___,0,0x8EF),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,2,0xC06),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_4,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(B_5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(As5,0,0x001),
    DN(___,0,0x000),
    DN(___,0,0xD01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P12[] = {
    DN(Cs4,3,0x000),
    DN(___,0,0x210),
    DN(___,0,0x210),
    DN(___,0,0x210),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P13[] = {
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(E_6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0xC00),
    DN(Gs6,8,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(E_6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_5,8,0x000),
    DN(___,0,0xC00),
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(E_6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0xC00),
    DN(Gs6,8,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(Gs6,8,0x000),
    DN(___,0,0xC00),
    DN(B_6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(Gs6,8,0x000),
    DN(___,0,0xC00),
    DN(As6,8,0x001),
    DN(___,0,0x000),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P15[] = {
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(E_6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0xC00),
    DN(Gs6,8,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(E_6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_5,8,0x000),
    DN(___,0,0xC00),
    DN(Cs6,8,0x000),
    DN(___,0,0xC00),
    DN(E_6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0xC00),
    DN(Gs6,8,0x482),
    DN(___,0,0x482),
    DN(Gs6,8,0x000),
    DN(___,0,0xC00),
    DN(B_6,8,0x000),
    DN(___,0,0xC00),
    DN(Cs7,8,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P16[] = {
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(___,0,0x000),
    DN(Cs4,9,0xE06),
    DN(Cs4,9,0xE06),
    DN(Gs3,9,0xE06),
    DN(___,0,0x000),
    DN(Gs3,9,0x000),
    DN(___,0,0x000),
    DN(Gs3,9,0xE06),
    DN(___,0,0x000),
    DN(Gs3,9,0xE06),
    DN(___,0,0x000),
    DN(Gs3,9,0x000),
    DN(___,0,0x000),
    DN(Gs3,9,0xE06),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P17[] = {
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(Fs5,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P18[] = {
    DN(A_3,9,0xE06),
    DN(___,0,0x000),
    DN(A_3,9,0x000),
    DN(___,0,0x000),
    DN(A_3,9,0xE06),
    DN(___,0,0x000),
    DN(A_3,9,0x000),
    DN(___,0,0x000),
    DN(A_3,9,0xE06),
    DN(___,0,0x000),
    DN(A_3,9,0xE06),
    DN(A_3,9,0xE06),
    DN(Fs3,9,0xE06),
    DN(___,0,0x000),
    DN(Fs3,9,0x000),
    DN(___,0,0x000),
    DN(Fs3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0x000),
    DN(B_3,9,0x000),
    DN(___,0,0x000),
    DN(B_3,9,0xE06),
    DN(___,0,0xD01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P19[] = {
    DN(A_6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs6,8,0x000),
    DN(___,0,0xC00),
    DN(Fs6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_6,8,0x000),
    DN(Fs6,8,0x000),
    DN(Gs6,8,0x000),
    DN(___,0,0x000),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(B_6,8,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x482),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P21[] = {
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(E_5,7,0x000),
    DN(___,0,0x000),
    DN(Ds5,7,0x000),
    DN(Cs5,7,0x000),
    DN(Ds5,7,0x000),
    DN(___,0,0x000),
    DN(B_4,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Fs5,7,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,7,0x000),
    DN(___,0,0x000),
    DN(Gs5,7,0x000),
    DN(___,0,0x000),
    DN(As5,7,0x000),
    DN(B_5,7,0x000),
    DN(As5,7,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xB04),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P22[] = {
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_4,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,0,0x000),
    DN(___,0,0x000),
    DN(E_5,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,0,0x000),
    DN(___,0,0x000),
    DN(B_5,0,0x000),
    DN(___,0,0x000),
    DN(Cs6,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xD01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};

static const unsigned char* const order1[] = {P0,P4,P4,P4,P11,P22,P17,P4,P21};
static const unsigned char* const order2[] = {P1,P5,P5,P10,P12,P16,P18,P10,P10};
static const unsigned char* const order3[] = {P2,P6,P8,P9,P13,P15,P19,P6,P8};
static const unsigned char* const order4[] = {P2,P7,P7,P7,P7,P7,P7,P7,P7};

static const hUGEDutyInstr_t duty_instruments[] = {
    {8,0,240,0,128},
    {8,64,240,0,128},
    {8,128,176,0,128},
    {8,192,240,0,128},
    {8,0,241,0,128},
    {8,64,241,0,128},
    {8,128,180,0,128},
    {8,192,241,0,128},
    {8,128,241,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
};
static const hUGEWaveInstr_t wave_instruments[] = {
    {0,32,0,0,128},
    {0,32,1,0,128},
    {0,32,2,0,128},
    {0,32,3,0,128},
    {0,32,4,0,128},
    {0,32,5,0,128},
    {0,32,6,0,128},
    {0,32,7,0,128},
    {0,32,8,0,128},
    {0,32,9,0,128},
    {0,32,10,0,128},
    {0,32,11,0,128},
    {0,32,12,0,128},
    {0,32,13,0,128},
    {0,32,14,0,128},
};
static const hUGENoiseInstr_t noise_instruments[] = {
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
};

static const unsigned char waves[] = {
    0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,
    0,1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,
    254,220,186,152,118,84,50,16,18,52,86,120,154,188,222,255,
    83,33,17,35,106,222,238,236,83,33,17,35,106,222,238,236,
    0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,
    254,252,250,248,246,244,242,240,242,244,246,248,250,252,254,255,
    254,221,204,187,170,153,136,119,138,189,241,36,87,138,189,238,
    132,17,97,237,87,71,90,173,206,163,23,121,221,32,3,71,
    88,149,134,56,98,45,9,181,126,28,35,163,173,82,10,173,
    71,168,94,201,165,205,58,136,190,28,35,187,209,212,201,26,
    38,17,50,135,160,86,236,105,10,163,10,42,216,117,121,85,
    42,14,169,38,11,126,163,121,1,110,69,107,234,156,52,67,
    64,198,215,54,214,172,231,197,48,96,172,34,39,197,188,155,
};

const hUGESong_t dungeon_stroll = {8, &order_cnt, order1, order2, order3,order4, duty_instruments, wave_instruments, noise_instruments, NULL, waves};
