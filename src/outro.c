#include "core.h"
#include "ui.h"

#define LINE_DURATION   90

BANKREF_EXTERN(gold_star)
extern hUGESong_t gold_star;

const char *outroText = \
"The tyrannical demon defeated,\n\
our four heroes sought to\n\
improve life for all monsters.\n\n\
Hour-long lunch breaks were\n\
instituted, the kitchen was\n\
expanded, and they bought a\n\
pool table.\n\n\
To this day, annual pool\n\
tournaments are held in their\n\
honour.\n\n\
The end. Thanks for playing!";

const uint8_t palettes[] = {
    DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_WHITE, DMG_WHITE),
    DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY),
    DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY),
    DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK),
};

uint8_t cutoff = 8;
uint8_t advanceTimer = LINE_DURATION;

void onScanlineInterrupt() {
    if (LY_REG < cutoff)    BGP_REG = palettes[3];
    else                    BGP_REG = palettes[0];
}

void stateInitOutro() {
    HIDE_BKG;
    HIDE_SPRITES;
    stopMusic();
    releaseAllBkgGfx();
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);
    startMusic(&gold_star, BANK(gold_star));
    renderText(1, 1, outroText);
    BGP_REG = palettes[0];
    SHOW_BKG;

    CRITICAL {
        STAT_REG = STATF_MODE00;
        add_LCD(onScanlineInterrupt);
        add_LCD(nowait_int_handler);
    }
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
}

void stateUpdateOutro() {
    if (cutoff < 144) {
        if (--advanceTimer == 0) {
            cutoff += 8;
            advanceTimer = LINE_DURATION;
        }
        if (cutoff >= 144) set_interrupts(VBL_IFLAG);
        BGP_REG = palettes[3];
    }
}

