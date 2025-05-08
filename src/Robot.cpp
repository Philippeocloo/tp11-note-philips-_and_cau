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
    int index = indexOfCell(i_board, X, Y);
    if(index < 0 ){
        return true;
    }
    Cell target_cell = i_board->getCells()[index]; 
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

        int index_cell = indexOfCell(i_board, x, y);
        if (index_cell >= 0) {
            setCell(i_board->getCells()[index_cell]);
        } else {
            break; 
        }
    }
}

bool Robot::onTarget(Target i_target) {
    Target currentTarget = m_cell.getTarget();

    if (currentTarget == i_target && m_color == i_target.getColor()) {
        return true;
    }   
    return false;
}