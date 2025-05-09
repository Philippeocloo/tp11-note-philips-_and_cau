#include "Robot.h"
#include "Cell.h"
#include "Board.h"
#include "Target.h"
#include "enums/Direction.h"
#include "enums/Border.h"
#include "enums/Shape.h"
#include <iostream>


Robot::Robot(RColor i_color, Cell* i_cell): m_color(i_color), m_cell(i_cell) {}


Cell* Robot::getCell() {
    return m_cell;
}


RColor Robot::getColor() const {
    return m_color;
}

void Robot::setCell(Cell* i_newCell) {
    m_cell = i_newCell;
}

bool Robot::checkifobstacle(Direction dir, Board* i_board){
    int X = m_cell->getX();
    int Y = m_cell->getY();

    switch (dir) {
        case Direction::UP: Y++; break;
        case Direction::DOWN: Y--; break;
        case Direction::LEFT: X--; break;
        case Direction::RIGHT: X++; break;
        default: return true;
    }
    if( X<0 || Y<0 || X >= TAILLE_X || Y >= TAILLE_Y ){
        return true;
    }
    Cell& target_cell = i_board->getCell(X,Y); 
    if(target_cell.hasRobot() || target_cell.hasTarget() ){
         return true;
    }
    else {
        return false;
    }
}

void Robot::move(Direction i_direction, Board* i_board){
    while (!checkifobstacle(i_direction, i_board)) {
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
        setCell(&i_board->getCell(x,y));
    }
}

bool Robot::onTarget(Target i_target) {
    Target currentTarget = m_cell->getTarget();

    if (currentTarget == i_target && m_color == i_target.getColor()) {
        return true;
    }   
    return false;
}