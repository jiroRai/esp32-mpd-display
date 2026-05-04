/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --stride 1 --align 1 --font fusion-pixel-10px-monospaced-zh_hans.ttf --symbols ⏸■★☆☎☏⚑⚐☀☼♚♛♜♝♞♟♔♕♖♗♘♙♠♡♢♣♤♥♦♧☺☹⚓⚔✈☯♂♀♩♪♫♬⇦⇧⇨⇩☜☝☞☟ --range 32-126 --format lvgl -o fusion_pixel_10.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef FUSION_PIXEL_10
#define FUSION_PIXEL_10 1
#endif

#if FUSION_PIXEL_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfa,

    /* U+0022 "\"" */
    0xb4,

    /* U+0023 "#" */
    0x5f, 0x59, 0xaf, 0xa0,

    /* U+0024 "$" */
    0x27, 0xaa, 0x63, 0x3e, 0x20,

    /* U+0025 "%" */
    0x91, 0x22, 0x48, 0x90,

    /* U+0026 "&" */
    0x4a, 0xa4, 0xba, 0x50,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x29, 0x49, 0x12, 0x20,

    /* U+0029 ")" */
    0x89, 0x12, 0x52, 0x80,

    /* U+002A "*" */
    0xab, 0xaa,

    /* U+002B "+" */
    0x22, 0xf2, 0x20,

    /* U+002C "," */
    0x60,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x22, 0x44, 0x48, 0x80,

    /* U+0030 "0" */
    0x69, 0xbd, 0x99, 0x60,

    /* U+0031 "1" */
    0x59, 0x24, 0xb8,

    /* U+0032 "2" */
    0x69, 0x12, 0x48, 0xf0,

    /* U+0033 "3" */
    0x69, 0x12, 0x19, 0x60,

    /* U+0034 "4" */
    0x35, 0x59, 0x9f, 0x10,

    /* U+0035 "5" */
    0xf8, 0x8e, 0x11, 0xe0,

    /* U+0036 "6" */
    0x69, 0x8e, 0x99, 0x60,

    /* U+0037 "7" */
    0xf1, 0x12, 0x22, 0x20,

    /* U+0038 "8" */
    0x69, 0x96, 0x99, 0x60,

    /* U+0039 "9" */
    0x69, 0x97, 0x19, 0x60,

    /* U+003A ":" */
    0x88,

    /* U+003B ";" */
    0x40, 0x60,

    /* U+003C "<" */
    0x2a, 0x22,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0x88, 0xa8,

    /* U+003F "?" */
    0x69, 0x12, 0x20, 0x20,

    /* U+0040 "@" */
    0x69, 0xbb, 0xb8, 0x60,

    /* U+0041 "A" */
    0x69, 0x99, 0xf9, 0x90,

    /* U+0042 "B" */
    0xe9, 0x9e, 0x99, 0xe0,

    /* U+0043 "C" */
    0x69, 0x88, 0x89, 0x60,

    /* U+0044 "D" */
    0xe9, 0x99, 0x99, 0xe0,

    /* U+0045 "E" */
    0xf8, 0x8e, 0x88, 0xf0,

    /* U+0046 "F" */
    0xf8, 0x8e, 0x88, 0x80,

    /* U+0047 "G" */
    0x69, 0x88, 0xb9, 0x70,

    /* U+0048 "H" */
    0x99, 0x9f, 0x99, 0x90,

    /* U+0049 "I" */
    0xf2, 0x22, 0x22, 0xf0,

    /* U+004A "J" */
    0x11, 0x11, 0x99, 0x60,

    /* U+004B "K" */
    0x99, 0xac, 0xa9, 0x90,

    /* U+004C "L" */
    0x88, 0x88, 0x88, 0xf0,

    /* U+004D "M" */
    0x9f, 0xf9, 0x99, 0x90,

    /* U+004E "N" */
    0x9d, 0xdb, 0xb9, 0x90,

    /* U+004F "O" */
    0x69, 0x99, 0x99, 0x60,

    /* U+0050 "P" */
    0xe9, 0x9e, 0x88, 0x80,

    /* U+0051 "Q" */
    0x69, 0x99, 0x9a, 0x50,

    /* U+0052 "R" */
    0xe9, 0x9e, 0xa9, 0x90,

    /* U+0053 "S" */
    0x69, 0x86, 0x19, 0x60,

    /* U+0054 "T" */
    0xf2, 0x22, 0x22, 0x20,

    /* U+0055 "U" */
    0x99, 0x99, 0x99, 0x60,

    /* U+0056 "V" */
    0x99, 0x9a, 0xaa, 0xc0,

    /* U+0057 "W" */
    0x99, 0x99, 0xff, 0x90,

    /* U+0058 "X" */
    0x99, 0x96, 0x99, 0x90,

    /* U+0059 "Y" */
    0x99, 0x55, 0x22, 0x20,

    /* U+005A "Z" */
    0xf1, 0x24, 0x48, 0xf0,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0xe0,

    /* U+005C "\\" */
    0x88, 0x44, 0x22, 0x21, 0x10,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0xe0,

    /* U+005E "^" */
    0x54,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x61, 0x79, 0x70,

    /* U+0062 "b" */
    0x88, 0xe9, 0x99, 0xe0,

    /* U+0063 "c" */
    0x69, 0x89, 0x60,

    /* U+0064 "d" */
    0x11, 0x79, 0x99, 0x70,

    /* U+0065 "e" */
    0x69, 0xf8, 0x60,

    /* U+0066 "f" */
    0x34, 0xf4, 0x44, 0x40,

    /* U+0067 "g" */
    0x79, 0x97, 0x16,

    /* U+0068 "h" */
    0x88, 0xe9, 0x99, 0x90,

    /* U+0069 "i" */
    0x20, 0xe2, 0x22, 0xf0,

    /* U+006A "j" */
    0x23, 0x92, 0x4e,

    /* U+006B "k" */
    0x88, 0x9a, 0xca, 0x90,

    /* U+006C "l" */
    0xc4, 0x44, 0x44, 0x30,

    /* U+006D "m" */
    0x9f, 0xf9, 0x90,

    /* U+006E "n" */
    0xe9, 0x99, 0x90,

    /* U+006F "o" */
    0x69, 0x99, 0x60,

    /* U+0070 "p" */
    0xe9, 0x9e, 0x88,

    /* U+0071 "q" */
    0x79, 0x97, 0x11,

    /* U+0072 "r" */
    0xbc, 0x88, 0x80,

    /* U+0073 "s" */
    0x78, 0x61, 0xe0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x30,

    /* U+0075 "u" */
    0x99, 0x99, 0x70,

    /* U+0076 "v" */
    0x99, 0xaa, 0xc0,

    /* U+0077 "w" */
    0x99, 0xff, 0x90,

    /* U+0078 "x" */
    0x99, 0x69, 0x90,

    /* U+0079 "y" */
    0x99, 0x55, 0x2c,

    /* U+007A "z" */
    0xf2, 0x48, 0xf0,

    /* U+007B "{" */
    0x34, 0x44, 0x84, 0x44, 0x30,

    /* U+007C "|" */
    0xff, 0x80,

    /* U+007D "}" */
    0xc2, 0x22, 0x12, 0x22, 0xc0,

    /* U+007E "~" */
    0x5a,

    /* U+21E6 "⇦" */
    0x8, 0xc, 0xb, 0xe8, 0x18, 0xa, 0x4, 0xbe,
    0x30, 0x8, 0x0,

    /* U+21E7 "⇧" */
    0x8, 0xa, 0x8, 0x88, 0x2e, 0x39, 0x10, 0x88,
    0x44, 0x3e, 0x0,

    /* U+21E8 "⇨" */
    0x8, 0x6, 0x3e, 0x90, 0x28, 0xc, 0xb, 0xe8,
    0x18, 0x8, 0x0,

    /* U+21E9 "⇩" */
    0x3e, 0x11, 0x8, 0x84, 0x4e, 0x3a, 0x8, 0x88,
    0x28, 0x8, 0x0,

    /* U+23F8 "⏸" */
    0xde, 0xf7, 0xbd, 0x80,

    /* U+25A0 "■" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x80,

    /* U+2600 "☀" */
    0x8, 0x20, 0x87, 0x7, 0xcb, 0xe9, 0xf0, 0x70,
    0x82, 0x8, 0x0,

    /* U+2605 "★" */
    0x8, 0x4, 0x7, 0x1f, 0xf3, 0xe0, 0xe0, 0xd8,
    0x44, 0x41, 0x0,

    /* U+2606 "☆" */
    0x8, 0x4, 0x5, 0x1e, 0xf4, 0x11, 0x50, 0xd8,
    0x44, 0x41, 0x0,

    /* U+260E "☎" */
    0x3e, 0x7f, 0xff, 0xfb, 0xb3, 0xe3, 0xfb, 0x8f,
    0xc7, 0xff, 0x80,

    /* U+260F "☏" */
    0x3e, 0x60, 0xe7, 0x3c, 0x72, 0x22, 0xa, 0x73,
    0x29, 0xff, 0x80,

    /* U+261C "☜" */
    0x18, 0xa, 0x3e, 0x90, 0x76, 0x29, 0x14, 0x4a,
    0x1f,

    /* U+261D "☝" */
    0xc, 0x14, 0x34, 0x47, 0x85, 0x82, 0xfc, 0x88,
    0xf8,

    /* U+261E "☞" */
    0xc, 0xa, 0xb, 0xfc, 0x1a, 0x35, 0x12, 0x91,
    0xf0,

    /* U+261F "☟" */
    0xf8, 0x88, 0xfc, 0x82, 0x85, 0x47, 0x34, 0x14,
    0xc,

    /* U+262F "☯" */
    0x3e, 0x3e, 0xbb, 0x3f, 0x9f, 0x8f, 0x87, 0x92,
    0xc2, 0x3e, 0x0,

    /* U+2639 "☹" */
    0x3e, 0x20, 0xa5, 0x32, 0x98, 0xc, 0xe6, 0x8a,
    0x82, 0x3e, 0x0,

    /* U+263A "☺" */
    0x3e, 0x20, 0xa5, 0x32, 0x98, 0xd, 0x16, 0x72,
    0x82, 0x3e, 0x0,

    /* U+263C "☼" */
    0x8, 0x20, 0x87, 0x4, 0x4a, 0x29, 0x10, 0x70,
    0x82, 0x8, 0x0,

    /* U+2640 "♀" */
    0x38, 0x89, 0x12, 0x23, 0x82, 0x3f, 0x88, 0x10,

    /* U+2642 "♂" */
    0xf, 0x80, 0xc0, 0xa0, 0x97, 0x8c, 0x42, 0x21,
    0x10, 0x70, 0x0,

    /* U+2654 "♔" */
    0x8, 0xe, 0x1a, 0xd2, 0x98, 0x8c, 0x45, 0xfc,
    0x82, 0x7f, 0x0,

    /* U+2655 "♕" */
    0x8, 0x24, 0x8a, 0x93, 0x96, 0x31, 0x10, 0xf8,
    0x44, 0x3e, 0x0,

    /* U+2656 "♖" */
    0x49, 0x3f, 0x90, 0x4f, 0xe2, 0x21, 0x11, 0xfd,
    0x1, 0xff, 0x80,

    /* U+2657 "♗" */
    0x10, 0x51, 0x55, 0xd9, 0x28, 0x9f, 0x41, 0xfe,

    /* U+2658 "♘" */
    0xc, 0x65, 0x2c, 0x1b, 0xba, 0x4f, 0x21, 0x7e,

    /* U+2659 "♙" */
    0x38, 0x89, 0x12, 0x23, 0x88, 0x91, 0x41, 0xfe,

    /* U+265A "♚" */
    0x8, 0xe, 0x1a, 0xde, 0xff, 0xff, 0xbd, 0xdc,
    0x82, 0x7f, 0x0,

    /* U+265B "♛" */
    0x8, 0x24, 0x8a, 0x93, 0x97, 0xf1, 0xf0, 0xf8,
    0x44, 0x3e, 0x0,

    /* U+265C "♜" */
    0x49, 0x3f, 0x90, 0x4f, 0xe3, 0xe1, 0xf1, 0xfd,
    0x1, 0xff, 0x80,

    /* U+265D "♝" */
    0x10, 0x71, 0xb6, 0x3e, 0xef, 0x9f, 0x41, 0xfe,

    /* U+265E "♞" */
    0xc, 0x7d, 0xdf, 0xfc, 0xe3, 0xcf, 0x21, 0x7e,

    /* U+265F "♟" */
    0x38, 0xf9, 0xf3, 0xe3, 0x88, 0x9f, 0x3e, 0xfe,

    /* U+2660 "♠" */
    0x8, 0xe, 0xf, 0x8f, 0xef, 0xff, 0xfd, 0xac,
    0x10, 0x3e, 0x0,

    /* U+2661 "♡" */
    0x63, 0x4a, 0x62, 0x30, 0x18, 0xa, 0x8, 0x88,
    0x28, 0x8, 0x0,

    /* U+2662 "♢" */
    0x8, 0xa, 0x8, 0x88, 0x28, 0xa, 0x8, 0x88,
    0x28, 0x8, 0x0,

    /* U+2663 "♣" */
    0x1c, 0x1f, 0x7, 0xd, 0x6f, 0xff, 0xfd, 0xac,
    0x10, 0x3e, 0x0,

    /* U+2664 "♤" */
    0x8, 0xa, 0x8, 0x88, 0x28, 0xc, 0xa5, 0xac,
    0x10, 0x3e, 0x0,

    /* U+2665 "♥" */
    0x63, 0x7b, 0xff, 0xff, 0xff, 0xfb, 0xf8, 0xf8,
    0x38, 0x8, 0x0,

    /* U+2666 "♦" */
    0x8, 0xe, 0xf, 0x8f, 0xef, 0xfb, 0xf8, 0xf8,
    0x38, 0x8, 0x0,

    /* U+2667 "♧" */
    0x1c, 0x11, 0x8, 0x8a, 0xa8, 0xc, 0xa5, 0xac,
    0x10, 0x3e, 0x0,

    /* U+2669 "♩" */
    0x24, 0x92, 0x5f, 0xc0,

    /* U+266A "♪" */
    0x21, 0x8a, 0x52, 0x91, 0x9c, 0xc0,

    /* U+266B "♫" */
    0x7, 0x9c, 0x48, 0x24, 0x12, 0x9, 0xd, 0x8f,
    0xc6, 0xc0, 0x0,

    /* U+266C "♬" */
    0x7, 0x9c, 0x49, 0xe7, 0x12, 0x9, 0xd, 0x8f,
    0xc6, 0xc0, 0x0,

    /* U+2690 "⚐" */
    0xf0, 0x8f, 0x81, 0x81, 0x81, 0xf1, 0x8f, 0x80,
    0x80,

    /* U+2691 "⚑" */
    0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x80,
    0x80,

    /* U+2693 "⚓" */
    0x8, 0xa, 0x2, 0x7, 0xc0, 0x80, 0x42, 0x72,
    0xfe, 0x1c, 0x0,

    /* U+2694 "⚔" */
    0x80, 0xa0, 0x88, 0x82, 0x80, 0x84, 0xa7, 0x8e,
    0xc6, 0xb6, 0x80,

    /* U+2708 "✈" */
    0x10, 0xe, 0x26, 0x19, 0x8f, 0xfe, 0x62, 0x60,
    0x38, 0x10, 0x0,

    /* U+F8EC "" */
    0x7f, 0x40, 0x60, 0xb3, 0x99, 0x4c, 0xe6, 0x3,
    0x1, 0x7f, 0x0,

    /* U+F8ED "" */
    0x7f, 0xe0, 0x74, 0xba, 0x5c, 0xe, 0x7, 0xcd,
    0xe8, 0x18, 0x0,

    /* U+F8EE "" */
    0x10, 0x38, 0x58, 0x81, 0xa, 0x24, 0x48, 0x60,

    /* U+F8EF "" */
    0x7f, 0x7f, 0xf9, 0xfc, 0x3e, 0x7f, 0xfd, 0xfc,

    /* U+F8F0 "" */
    0x41, 0x11, 0x1f, 0xd0, 0x18, 0xd, 0x16, 0x3,
    0x1, 0x7f, 0x0,

    /* U+F8F1 "" */
    0x3, 0x63, 0xd9, 0xde, 0xe7, 0xf3, 0xf8, 0xf8,
    0x38, 0xf8, 0x0,

    /* U+F8F2 "" */
    0xe0, 0xc8, 0x92, 0x84, 0x81, 0x40, 0x90, 0xa4,
    0x89, 0x83, 0x80,

    /* U+F8F3 "" */
    0x6, 0x0, 0x8d, 0x2f, 0x5f, 0xf6, 0x4f, 0x57,
    0x93, 0x3e, 0x0,

    /* U+F8F4 "" */
    0x7f, 0x7c, 0xfd, 0xfe, 0xfc, 0x1f, 0xbf, 0xdf,
    0xef, 0x77, 0x0,

    /* U+F8F5 "" */
    0x36, 0x3f, 0x9f, 0xdb, 0xbf, 0xff, 0xfd, 0x8c,

    /* U+F8F6 "" */
    0xff, 0xe0, 0xf7, 0xf8, 0x3f, 0xda, 0xe9, 0x8c,
    0x7c, 0x1c, 0x0,

    /* U+F8F7 "" */
    0x22, 0xe, 0xa, 0x97, 0xd8, 0xd, 0xf6, 0xfb,
    0x7d, 0x14, 0x0,

    /* U+F8F8 "" */
    0x3e, 0x2e, 0xb2, 0x7c, 0x7c, 0x9c, 0xe6, 0xfa,
    0xfe, 0x3e, 0x0,

    /* U+F8F9 "" */
    0xc, 0x5, 0x2, 0x81, 0x7, 0x84, 0x5a, 0x72,
    0xd1, 0xf, 0x0,

    /* U+F8FA "" */
    0x77, 0x4b, 0xed, 0xf2, 0xf9, 0x7c, 0xbe, 0x57,
    0x2f, 0x77, 0x0,

    /* U+F8FB "" */
    0x3e, 0x3c, 0xbd, 0xbe, 0xdf, 0x9d, 0x9f, 0x1e,
    0xde, 0x3e, 0x0,

    /* U+F8FC "" */
    0x22, 0x2a, 0x92, 0x51, 0x19, 0x4c, 0xa5, 0x8c,

    /* U+F8FD "" */
    0xc0, 0x7b, 0x3d, 0xfe, 0xf0, 0x7, 0xbf, 0xdf,
    0xec, 0xc0, 0x0,

    /* U+F8FE "" */
    0x1c, 0x1f, 0x17, 0x4d, 0x64, 0x91, 0xb9, 0x57,
    0x93, 0xc1, 0x80,

    /* U+F8FF "" */
    0x8, 0x21, 0xb7, 0xff, 0xdf, 0xbf, 0xff, 0x6c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 80, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 3, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 12, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 80, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 21, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 25, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 36, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 80, .box_w = 1, .box_h = 5, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 80, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 84, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 88, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 206, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 211, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 215, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 216, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 217, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 218, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 242, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 253, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 273, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 276, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 301, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 309, .adv_w = 80, .box_w = 1, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 311, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 316, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 317, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 328, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 339, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 350, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 361, .adv_w = 160, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 365, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 376, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 387, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 398, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 409, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 420, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 431, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 449, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 467, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 478, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 489, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 500, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 511, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 519, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 530, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 541, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 552, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 563, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 571, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 579, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 587, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 598, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 609, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 620, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 628, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 636, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 644, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 655, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 666, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 677, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 688, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 699, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 710, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 721, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 732, .adv_w = 160, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 736, .adv_w = 160, .box_w = 5, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 742, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 753, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 764, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 773, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 782, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 793, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 804, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 815, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 826, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 837, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 845, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 864, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 875, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 886, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 897, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 908, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 916, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 927, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 938, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 949, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 960, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 971, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 982, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1001, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1012, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x2, 0x3, 0x212, 0x3ba, 0x41a, 0x41f,
    0x420, 0x428, 0x429, 0x436, 0x437, 0x438, 0x439, 0x449,
    0x453, 0x454, 0x456, 0x45a, 0x45c
};

static const uint16_t unicode_list_3[] = {
    0x0, 0x1, 0x2, 0x3, 0x27, 0x28, 0x2a, 0x2b,
    0x9f
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8678, .range_length = 1117, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 21, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 9812, .range_length = 20, .glyph_id_start = 117,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 9833, .range_length = 160, .glyph_id_start = 137,
        .unicode_list = unicode_list_3, .glyph_id_ofs_list = NULL, .list_length = 9, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 63724, .range_length = 20, .glyph_id_start = 146,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 5,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t fusion_pixel_10 = {
#else
lv_font_t fusion_pixel_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 9,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FUSION_PIXEL_10*/
