#pragma once

#include <vector>
#include <iostream>

#include "enums/Border.h"
#include "Target.h"
#include "Robot.h"

/**
 * @class Cell
 * @brief Représente une case du plateau de jeu.
 *
 * Chaque cellule peut contenir un robot, une cible, et des informations sur ses bordures.
 */

class Robot;

class Cell {
private:
    int m_x;
    int m_y;

    Border m_border;
    Robot* m_robot;
    Target* m_target;

public:

// Constructeurs
    Cell() : m_x(0), m_y(0), m_border(Border::NONE), m_robot(nullptr), m_target(nullptr){};
    Cell(int x, int y);

// Getters
    int getX() const { return this->m_x; };
    int getY() const { return this->m_y; };
    Target* getTarget() { return this->m_target; };
    Border getBorder() const { return this->m_border; }

// Setters
    void setBorder(Border i_border);
    void setTarget(Target* i_target);
    void setRobot(Robot* i_robot);

// Autres méthodes
    bool hasTarget() const { return m_target != nullptr; }; 
    bool hasRobot() const { return m_robot != nullptr; };

};
