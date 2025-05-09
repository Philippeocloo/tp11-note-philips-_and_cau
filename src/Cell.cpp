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
