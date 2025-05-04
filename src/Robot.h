#pragma once

#include "enums/Color.h"

#include "string"

class Robot {
private:
    int x;
    int y;
    Color color;

public:
    Robot(int x, int y, Color couleur);
    void deplacement(const std::string& direction);

    //Guetteurs
    int getX() const;
    int getY() const;
    Color getCouleur() const;
};