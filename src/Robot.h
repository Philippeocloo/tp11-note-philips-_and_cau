#pragma once

#include "enums/Color.h"

#include "string"

class Robot {
private:
    int m_x;
    int m_y;
    Color m_color;

public:
    Robot(int i_x, int i_y, Color i_couleur);
    void move(const std::string& i_direction);

    //Guetteurs
    int getX() const;
    int getY() const;
    Color getCouleur() const;
};