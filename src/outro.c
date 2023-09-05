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

uint8_t advanceTimer = LINE_DURATION;

void onScanlineInterrupt() {
    BGP_REG = palettes[0];
}

void stateInitOutro() {
    HIDE_BKG;
    HIDE_SPRITES;
    stopMusic();
    releaseAllBkgGfx();
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0x00u);
    startMusic(&gold_star, BANK(gold_star));
    BGP_REG = palettes[0];
    renderText(1, 1, outroText);
    SHOW_BKG;

    CRITICAL {
        STAT_REG = STATF_LYC;
        add_LCD(onScanlineInterrupt);
    }
    LYC_REG = 8;
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
}

void stateUpdateOutro() {
    if (LYC_REG < 144) {
        if (--advanceTimer == 0) {
            LYC_REG += 8;
            advanceTimer = LINE_DURATION;
        }
        if (LYC_REG >= 144) set_interrupts(VBL_IFLAG);
        BGP_REG = palettes[3];
    }
}

