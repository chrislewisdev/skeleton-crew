#ifndef UI_H
#define UI_H

typedef struct MenuItem {
    const char *description;
    void (*action)();
} MenuItem;

typedef struct Menu {
    uint8_t x, y;
    uint8_t width, height;
    uint8_t selectedIndex;
    uint8_t itemsSize;
    MenuItem* items;
} Menu;

void initUi();
inline void render9slice(uint8_t x, uint8_t y, uint8_t width, uint8_t height); 
inline void renderText(uint8_t x, uint8_t y, const char *text);
inline void renderNumber(uint8_t x, uint8_t y, uint8_t value);
inline void renderMenu(Menu *menu);
inline void renderCursor(uint8_t x, uint8_t y);
void updateMenu(Menu *menu);

#endif

