#pragma once

#include "enums/Color.h"
#include "enums/Direction.h"

class Cell;
class Board;
class Target;

class Robot {
private:
    RColor m_color;
    Cell* m_cell;

public:

//Constructeurs
    Robot(RColor i_couleur, Cell* i_cell);

//Getters
    Cell* getCell() const { return m_cell; };
    RColor getColor() const {return m_color; };

//Setters
    void setCell(Cell* i_cell);

// Autres méthodes
    bool checkIfObstacle(Direction dir, Board* i_board) ;
    bool onTarget(Target i_target);
    void move(Direction i_direction, Board* i_board);
};