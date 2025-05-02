#include "Case.h"

Case::Case(int i_x, int i_y) {
    this->m_x = i_x;
    this->m_y = i_y;
}

//Getters
Target Case::getTarget() {
    return this->m_target;
}

//Setters
void Case::setBorder(Border i_border) {
    this->m_border = i_border;
}
