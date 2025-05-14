#include "Robot.h"
#include "Cell.h"
#include "Board.h"
#include "Target.h"
#include "enums/Direction.h"
#include "enums/Border.h"
#include "enums/Shape.h"
#include <iostream>

//--------------CONSTRUCTEUR------------------//
/**
 * @file Robot.cpp
 * @brief Implémente les méthodes de la classe Robot, représentant un robot sur le plateau de jeu.
 */
Robot::Robot(RColor i_color, Cell* i_cell): m_color(i_color), m_cell(i_cell) {}
//____________________________________________//

//--------------SETTERS-----------------------//
/**
 * @brief Met à jour la cellule actuelle du robot
 * @param i_newCell Nouvelle cellule assignée au robot
 */
void Robot::setCell(Cell* i_newCell) {
    m_cell = i_newCell;
}
//____________________________________________//


//--------------AUTRES METHODES-----------------------//

/**
 * @brief Vérifie si un obstacle empêche le robot d'avancer dans la direction donnée
 * @param dir Direction de déplacement souhaitée
 * @param i_board Plateau sur lequel se trouve le robot
 * @return true si un obstacle bloque le déplacement, false sinon
 */
bool Robot::checkIfObstacle(Direction dir, Board* i_board) {
    if (!m_cell || !i_board) return true;

    int X = m_cell->getX();
    int Y = m_cell->getY();

    //Verifier case actuelle
    Border currentBorder = m_cell->getBorder();

    switch (dir) {
        case Direction::UP:    
            if(currentBorder == Border::NE || currentBorder == Border::NW) return true;
        break;
        
        case Direction::DOWN:  
            if(currentBorder == Border::SE || currentBorder == Border::SW) return true;
        break;

        case Direction::LEFT:  
            if(currentBorder == Border::NW || currentBorder == Border::SW) return true;
        break;

        case Direction::RIGHT: 
            if(currentBorder == Border::NE || currentBorder == Border::SE) return true;
        break;
        default: break;
    }

    switch (dir) {
        case Direction::UP:    
            Y++; 
        break;
        
        case Direction::DOWN:  
            Y--; 
        break;

        case Direction::LEFT:  
            X--; 
        break;

        case Direction::RIGHT: 
            X++; 
        break;
        
        default: return true;
    }

    // Vérifie les limites du plateau
    if (X < 0 || Y < 0 || X >= TAILLE_X || Y >= TAILLE_Y) {
        return true;
    }

    Cell& target_cell = i_board->getCell(X,Y);

    // Obstacle : autre robot présent
    if (target_cell.hasRobot()) {
        return true;
    }

    // Obstacle : coin bloquant sur la cellule cible
    Border corner = target_cell.getBorder();

    switch (dir) {
        case Direction::UP:
            if (corner == Border::SE || corner == Border::SW) return true;
        break;

        case Direction::DOWN:
            if (corner == Border::NE || corner == Border::NW) return true;
        break;

        case Direction::LEFT:
            if (corner == Border::NE || corner == Border::SE) return true;
        break;

        case Direction::RIGHT:
            if (corner == Border::NW || corner == Border::SW) return true;
        break;
        
        default:
            return true;
    }

    return false; // Pas d'obstacle
}

/**
 * @brief Déplace le robot dans une direction donnée tant qu'aucun obstacle n'est rencontré
 * @param i_direction Direction dans laquelle déplacer le robot
 * @param i_board Plateau sur lequel effectuer le déplacement
 */
void Robot::move(Direction i_direction, Board* i_board){
    while (!checkIfObstacle(i_direction, i_board)) {
        int x = m_cell->getX();
        int y = m_cell->getY();

        // Calculer la nouvelle position
        switch (i_direction) {
            case Direction::UP:    y++; break;
            case Direction::DOWN:  y--; break;
            case Direction::LEFT:  x--; break;
            case Direction::RIGHT: x++; break;
            default: break;
        }
        if( x<0 || y<0 || x >= TAILLE_X || y >= TAILLE_Y ){
            break;
        }
        m_cell->setRobot(nullptr);
        setCell(&i_board->getCell(x,y));
        i_board->getCell(x,y).setRobot(this);
    }
}

/**
 * @brief Vérifie si le robot se trouve actuellement sur la cible donnée
 * @param i_target Cible à tester
 * @return true si le robot est sur la cible (même couleur ou MULTICOLOR), false sinon
 */
bool Robot::onTarget(Target* i_target) {
    Target* currentTarget = m_cell->getTarget();

   if (currentTarget == i_target && (m_color == i_target->getColor() || currentTarget->getColor() == RColor::MULTICOLOR)) {
        return true;
    }   
    return false;
}