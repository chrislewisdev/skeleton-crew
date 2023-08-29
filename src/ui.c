#include "core.h"
#include "ui.h"
#include "vwf.h"
#include "vwf_font.h"
#include "gen/ui9slice.h"
#include "gen/cursor.h"
#include "gen/numbers.h"

uint8_t baseNineSliceTile;
uint8_t baseNumbersTile;
uint8_t cursorTile, cursorSprite;

void initUi() {
    baseNineSliceTile = claimBkgGfx(ui9slice_TILE_COUNT, ui9slice_tiles);
    baseNumbersTile = claimSharedGfx(numbers_TILE_COUNT, numbers_tiles);
    cursorTile = claimObjGfx(cursor_TILE_COUNT, cursor_tiles);
    cursorSprite = claimSprite();

    set_sprite_tile(cursorSprite, cursorTile);
    set_sprite_prop(cursorSprite, 0);

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

inline void render9sliceToWindow(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    // Top edge
    set_win_tile_xy(x, y, baseNineSliceTile);
    for (uint8_t tx = x + 1; tx < x + width - 1; tx++) {
        set_win_tile_xy(tx, y, baseNineSliceTile + 1);
    }
    set_win_tile_xy(x + width - 1, y, baseNineSliceTile + 2);
    // Left-right edges
    for (uint8_t ty = y + 1; ty < y + height - 1; ty++) {
        set_win_tile_xy(x, ty, baseNineSliceTile + 3);
        set_win_tile_xy(x + width - 1, ty, baseNineSliceTile + 4);
    }
    // Bottom edge
    set_win_tile_xy(x, y + height - 1, baseNineSliceTile + 5);
    for (uint8_t tx = x + 1; tx < x + width - 1; tx++) {
        set_win_tile_xy(tx, y + height - 1, baseNineSliceTile + 6);
    }
    set_win_tile_xy(x + width - 1, y + height - 1, baseNineSliceTile + 7);
}

inline void renderText(uint8_t x, uint8_t y, const char *text) {
    // TODO: We should pre-render and re-use common text where appropriate
    // (e.g. menus) - not sure how to do this yet
    uint8_t tilesUsed = vwf_draw_text(x, y, gfxTileOffset, text);
    claimBkgGfxRaw(tilesUsed);
}

inline void renderNumber(uint8_t x, uint8_t y, uint8_t value) {
    uint8_t onesDigit = value % 10;
    uint8_t tensDigit = value / 10;

    set_bkg_tile_xy(x, y, baseNumbersTile + tensDigit);
    set_bkg_tile_xy(x + 1, y, baseNumbersTile + onesDigit);
}

inline void renderNumberAsSprite(uint8_t x, uint8_t y, uint8_t baseSprite, uint8_t value) {
    uint8_t onesDigit = value % 10;
    set_sprite_tile(baseSprite + 1, baseNumbersTile + onesDigit);
    move_sprite(baseSprite + 1, x + 8, y);

    if (value >= 10) {
        uint8_t tensDigit = value / 10;
        set_sprite_tile(baseSprite, baseNumbersTile + tensDigit);
        move_sprite(baseSprite, x, y);
    }
}

void renderMenu(Menu *menu) {
    render9slice(menu->x, menu->y, menu->width, menu->height);
    
    // Render items
    for (uint8_t i = 0; i < menu->itemsSize; i++) {
       renderText(menu->x + 1, menu->y + i + 1, menu->items[i].description);
    }
}

void unrenderMenu(Menu *menu) {
    fill_bkg_rect(menu->x, menu->y, menu->width, menu->height, 0);
}

inline void renderCursor(uint8_t x, uint8_t y) {
    move_sprite(cursorSprite, x, y);
}

void updateMenu(Menu* menu) {
    if (menu->selectedIndex >= menu->itemsSize) menu->selectedIndex = menu->itemsSize - 1;

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

