#include "Robot.h"
#include <iostream>

Robot::Robot(int i_x, int i_y, Color i_color)
    : m_x(i_x), m_y(i_y), m_color(i_color) {}

void Robot::move(const std::string& direction) {
    if (direction == "up") {
        m_y -= 1;
    } else if (direction == "down") {
        m_y += 1;
    } else if (direction == "left") {
        m_x -= 1;
    } else if (direction == "right") {
        m_x += 1;
    } else {
        std::cerr << "Erreur " << direction << std::endl;
    }
}

int Robot::getX() const {
    return m_x;
}

int Robot::getY() const {
    return m_y;
}

Color Robot::getCouleur() const {
    return m_color;
}
