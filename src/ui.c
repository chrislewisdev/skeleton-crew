#include "core.h"
#include "ui.h"
#include "vwf.h"
#include "vwf_font.h"
#include "gen/ui9slice.h"
#include "gen/cursor.h"

uint8_t baseNineSliceTile;
uint8_t cursorTile, cursorSprite;

void initUi() {
    baseNineSliceTile = claimBkgGfx(ui9slice_TILE_COUNT, ui9slice_tiles);
    cursorTile = claimObjGfx(cursor_TILE_COUNT, cursor_tiles);
    cursorSprite = claimSprite();

    set_sprite_tile(cursorSprite, cursorTile);

    vwf_set_destination(VWF_RENDER_BKG);
    vwf_load_font(0, vwf_font, (UBYTE)&__bank_vwf_font);
}

inline void render9slice(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    // Top edge
    set_bkg_tile_xy(x, y, baseNineSliceTile);
    for (uint8_t tx = x + 1; tx < x + width - 1; tx++) {
        set_bkg_tile_xy(tx, y, baseNineSliceTile + 1);
    }
    set_bkg_tile_xy(x + width - 1, y, baseNineSliceTile + 2);
    // Left-right edges
    for (uint8_t ty = y + 1; ty < y + height - 1; ty++) {
        set_bkg_tile_xy(x, ty, baseNineSliceTile + 3);
        set_bkg_tile_xy(x + width - 1, ty, baseNineSliceTile + 4);
    }
    // Bottom edge
    set_bkg_tile_xy(x, y + height - 1, baseNineSliceTile + 5);
    for (uint8_t tx = x + 1; tx < x + width - 1; tx++) {
        set_bkg_tile_xy(tx, y + height - 1, baseNineSliceTile + 6);
    }
    set_bkg_tile_xy(x + width - 1, y + height - 1, baseNineSliceTile + 7);
}

inline void renderText(uint8_t x, uint8_t y, const char *text) {
    // TODO: Work out how to utilise bkg gfx better...
    uint8_t tilesUsed = vwf_draw_text(x, y, gfxTileOffset, text);
    claimBkgGfxRaw(tilesUsed);
}

//inline void renderNumber(uint8_t x, uint8_t y, uint8_t value) {
//    uint8_t onesDigit = value % 10;
//    uint8_t tensDigit = value / 10;
//
//    set_bkg_tile_xy(x, y, NUMBERS_TILE_START + tensDigit);
//    set_bkg_tile_xy(x + 1, y, NUMBERS_TILE_START + onesDigit);
//}

void renderMenu(Menu *menu) {
    uint8_t x = menu->x;
    uint8_t y = menu->y;
    uint8_t width = menu->width;
    uint8_t height = menu->height;

    render9slice(x, y, width, height);
    
    // Render items
    for (uint8_t i = 0; i < menu->itemsSize; i++) {
       renderText(x + 1, y + i + 1, menu->items[i].description);
    }
}

//void unrenderMenu(Menu *menu) {
//    for (uint8_t x = menu->x; x < menu->x + menu->width; x++) {
//        for (uint8_t y = menu->y; y < menu->y + menu->height; y++) {
//            set_bkg_tile_xy(x, y, 0);
//        }
//    }
//}

void updateMenu(Menu* menu) {
    // Cursor controls
    if (KEYPRESSED(J_UP) && menu->selectedIndex > 0) {
        menu->selectedIndex--;
    } else if (KEYPRESSED(J_DOWN) && menu->selectedIndex < menu->itemsSize - 1) {
        menu->selectedIndex++;
    }

    if (KEYPRESSED(J_A) && menu->items[menu->selectedIndex].action != 0) {
        menu->items[menu->selectedIndex].action();
    }

    move_sprite(cursorSprite, menu->x * 8 + 8, (menu->y + 1 + menu->selectedIndex) * 8 + 16);
}

