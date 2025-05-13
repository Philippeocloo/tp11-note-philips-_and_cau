#include "Cell.h"

Cell::Cell(int i_x, int i_y) {
    this->m_x = i_x;
    this->m_y = i_y;
    m_border = Border::NONE;
    m_robot = nullptr;
}

//Setters
void Cell::setBorder(Border i_border) {
    this->m_border = i_border;
}

void Cell::setTarget(Target i_target, bool m_hasTarget){ 
    m_target = i_target; 
    this->m_hasTarget = m_hasTarget;
}

void Cell::setRobot(Robot* i_robot) { 
    m_robot = i_robot; 
}