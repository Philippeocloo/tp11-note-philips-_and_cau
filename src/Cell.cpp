#include "Cell.h"



/**
 * @brief Constructeur de la cellule
 * @details Initialise une cellule avec des coordonnées (x, y),
 *          sans robot ni cible, et sans bordure.
 * @param i_x Coordonnée horizontale
 * @param i_y Coordonnée verticale
 */
Cell::Cell(int i_x, int i_y) {
    this->m_x = i_x;
    this->m_y = i_y;
    m_border = Border::NONE;
    m_robot = nullptr;
    m_target = nullptr;
}

//Setters
/**
 * @brief Définit une bordure pour la cellule
 * @param i_border Bordure à appliquer à la cellule
 */
void Cell::setBorder(Border i_border) {
    this->m_border = i_border;
}

/**
 * @brief Place une cible dans la cellule
 * @param i_target Pointeur vers la cible à associer à cette cellule
 */
void Cell::setTarget(Target* i_target){ 
    m_target = i_target; 
}

/**
 * @brief Place un robot dans la cellule
 * @param i_robot Pointeur vers le robot à associer à cette cellule
 */
void Cell::setRobot(Robot* i_robot) { 
    m_robot = i_robot; 
}