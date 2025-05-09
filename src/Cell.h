#pragma once

#include <vector>
#include <iostream>

#include "enums/Border.h"
#include "Target.h"
#include "Robot.h"

class Robot;

class Cell {
private:
    int m_x;
    int m_y;

    Border m_border;
    Robot* m_robot;
    Target m_target;

    bool m_hasTarget = false;

public:

// Constructeurs
    Cell() : m_x(0), m_y(0), m_border(Border::NONE), m_robot(nullptr) {};
    Cell(int x, int y);

// Getters
    int getX() const { return this->m_x; };
    int getY() const { return this->m_y; };
    Target getTarget() { return this->m_target; };
    Border getBorder() const { return this->m_border; }

    

// Setters
    void setBorder(Border i_border);

    void setTarget(Target i_target, bool m_hasTarget) { 
        m_target = i_target; 
        this->m_hasTarget = m_hasTarget;
    }

    void setRobot(Robot* i_robot) { 
        m_robot = i_robot; 

    }

// Autres
    bool hasTarget() const { return m_hasTarget; }; 
    
    bool hasRobot() const { return m_robot != nullptr; };

};
