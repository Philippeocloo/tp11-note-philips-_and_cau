#pragma once

#include <enums/Color.h>
#include <raylib.h>

#undef RED
#undef GREEN
#undef BLUE
#undef YELLOW

#define R_RED (Color){ 230, 41, 55, 255 } 
#define R_GREEN (Color){ 0, 228, 48, 255 } 
#define R_YELLOW (Color){ 253, 249, 0, 255 }
#define R_BLUE (Color){ 0, 121, 241, 255 }

Color getColorFromRColor(RColor rcol);