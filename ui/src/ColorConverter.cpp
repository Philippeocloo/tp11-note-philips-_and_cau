#include "ColorConverter.h"

#include <iostream>

/// @brief Converts RColor (robot or target color) to a Raylib Color
/// @param rcol input rcolor
/// @return Raylib's Color
Color getColorFromRColor(RColor rcol) {
    Color drawColor;
    switch (rcol)
        {
        case RColor::RED:
            drawColor = R_RED;
            break;
        case RColor::BLUE:
            drawColor = R_BLUE;
            break;
        case RColor::GREEN:
            drawColor = R_GREEN;
            break;
        case RColor::YELLOW:
            drawColor = R_YELLOW;
            break;
        default:
            drawColor = BLACK;
            break;
    }

    return drawColor;
}