#include "ColorConverter.h"

#include <iostream>

/// @brief Converts RColor (robot or target color) to a Raylib Color
/// @param rcol input rcolor
/// @return Raylib's Color
Color getColorFromRColor(RColor rcol) {
    Color drawColor;
    switch (rcol)
        {
        case RColor::R_RED:
            drawColor = RED;
            break;
        case RColor::R_BLUE:
            drawColor = BLUE;
            break;
        case RColor::R_GREEN:
            drawColor = GREEN;
            break;
        case RColor::R_YELLOW:
            drawColor = YELLOW;
            break;
        default:
            drawColor = BLACK;
            break;
    }

    return drawColor;
}