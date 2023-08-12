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
inline void renderMenu(Menu *menu);
void updateMenu(Menu *menu);

#endif

