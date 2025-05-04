#pragma once

#include <vector>
#include <iostream>
#include "enums/Border.h"
#include "Target.h"
#include "Robot.h"

class Case {
private:
    const int m_x;
    const int m_y;

    Border m_border;
    Robot m_robot;
    Target m_target;

    bool m_hasRobot = false;
    bool m_hasTarget = false;

public:

// Constructeurs
    Case() : m_x(0), m_y(0) {};
    Case(int x, int y);

// Getters
    int getX() const { return this->m_x; };
    int getY() const { return this->m_y; };
    Target getTarget() { return this->m_target; };

    

// Setters
    void setBorder(Border i_border);

    void setTarget(Target i_target) { 
        m_target = i_target; 
        m_hasTarget = true;
    }

    void setRobot(Robot i_robot) { 
        m_robot = i_robot; 
        m_hasRobot = true; 
    }

// Autres
    bool hasTarget() const { return m_hasTarget; }; 
    
    bool hasRobot() const { return m_hasRobot; };

};
