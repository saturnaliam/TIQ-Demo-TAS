#define RIGHT 352
#define LEFT 166
#define DOWN 313
#define UP 228
#define COORD_OFFSET_X 8
#define COORD_OFFSET_Y 51

#include <Windows.h>
#include <vector>

struct TAS_MOVE {
    int scene;
    POINT cursorPosition;
};

const POINT TL = { LEFT, UP };
const POINT TR = { RIGHT, UP };
const POINT BL = { LEFT, DOWN };
const POINT BR = { RIGHT, DOWN };

// if you want to change these values, you can use cheat engine + some other program to get the scene and cursor position, or alternatively use 
// my tiq tasing tool program to find the needed values
const TAS_MOVE movements[] = {
    { 0, { 140, 330 } }, { 2, BR }, { 3, BL }, { 4, BR },
    { 5, TL }, { 6, TR }, { 7, BL },
    { 8, BR }, { 9, { 282, 280 } }, { 10, TR },
    { 11, TR }, { 12, { 300, 250 } }, { 13, TL },
    { 14, { 216, 280 } }, { 15, BL }, { 16, { 150, 50 } },
    { 17, TL }, { 18, { 446, 143 } }, { 19, BR },
    { 20, { 405, 216 } }, { 21, { 152, 215 } }, { 22, { 295, 325 } },
    { 23, { 174, 327 } }, { 24, { 340, 220 } }, { 25, { 390, 272 } },
    { 26, BR }, { 27, TL }, { 28, { 384, 289 } },
    { 29, TR }, { 30, TR }, { 31, BL },
    { 32, BR }, { 33, { 112, 146 } }, { 34, BL },
    { 35, BR }, { 36, { 350, 230 } }
};