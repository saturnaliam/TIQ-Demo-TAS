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
    { 0, { 236, 306 } }, { 2, BR }, { 3, BL }, { 4, BR },
    { 5, TL }, { 6, TR }, { 7, BL },
    { 8, BR }, { 9, { 286, 279 } }, { 10, TR },
    { 11, TR }, { 12, { 322, 226 } }, { 13, TL },
    { 14, { 166, 271 } }, { 15, BL }, { 16, { 152, 52 } },
    { 17, TL }, { 18, { 435, 152 } }, { 19, BR },
    { 20, { 396, 244 } }, { 21, { 165, 244 } }, { 22, { 279, 308 } },
    { 23, { 184, 313 } }, { 24, { 333, 238 } }, { 25, { 379, 256 } },
    { 26, BR }, { 27, TL }, { 28, { 384, 289 } },
    { 29, TR }, { 30, TR }, { 31, BL },
    { 32, BR }, { 33, { 187, 184 } }, { 34, BL },
    { 35, BR }, { 36, { 378, 261 } }
};