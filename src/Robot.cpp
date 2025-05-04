#include "Robot.h"
#include <iostream>

Robot::Robot(int x, int y, Color color)
    : x(x), y(y), color(color) {}

void Robot::deplacement(const std::string& direction) {
    if (direction == "haut") {
        y -= 1;
    } else if (direction == "bas") {
        y += 1;
    } else if (direction == "gauche") {
        x -= 1;
    } else if (direction == "droite") {
        x += 1;
    } else {
        std::cerr << "Direction inconnue : " << direction << std::endl;
    }
}

int Robot::getX() const {
    return x;
}

int Robot::getY() const {
    return y;
}

Color Robot::getCouleur() const {
    return color;
}
