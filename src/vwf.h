/**
 * VWF CODE THANKS TO TOXA FROM https://github.com/untoxa/VWF/tree/master
 *
MIT License

Copyright (c) 2020 Toxa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 *
 */

#ifndef _VWF_H_INCLUDE
#define _VWF_H_INCLUDE

#include <gbdk/platform.h>

#include <stdint.h>

#define __VWF_BANK_PREFIX(A) __bank_##A
#define TO_VWF_FARPTR(A) {.bank = (char)&(__VWF_BANK_PREFIX(A)), .ptr = (void *)&(A)}

#define RECODE_7BIT 1
#define FONT_VWF 2

#define VWF_MODE_RENDER 0
#define VWF_MODE_PRINT 1

typedef struct vwf_farptr_t {
    UINT8 bank;
    void * ptr;
} vwf_farptr_t;

typedef struct font_desc_t {
    uint8_t attr;
    const uint8_t * recode_table;
    const uint8_t * widths;
    const uint8_t * bitmaps;
} font_desc_t;

typedef enum { 
    VWF_RENDER_BKG, 
    VWF_RENDER_WIN 
} vwf_reder_dest_e;

extern vwf_farptr_t vwf_fonts[4];
extern uint8_t vwf_mode;

void vwf_set_destination(vwf_reder_dest_e destination);
void vwf_load_font(uint8_t idx, const void * font, uint8_t bank);
void vwf_activate_font(uint8_t idx);
uint8_t vwf_draw_text(uint8_t x, uint8_t y, uint8_t base_tile, const unsigned char * str);
uint8_t vwf_next_tile();

inline void vwf_set_mode(uint8_t mode) {
   vwf_mode = mode; 
}
inline void vwf_set_colors(uint8_t fgcolor, uint8_t bgcolor) {
    set_1bpp_colors(fgcolor, bgcolor);
}

#endif
