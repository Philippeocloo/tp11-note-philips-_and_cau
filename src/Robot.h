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
    Robot(RColor i_couleur, Cell* i_cell);
    bool checkIfObstacle(Direction dir, Board* i_board) ;
    bool onTarget(Target i_target);
    void move(Direction i_direction, Board* i_board);
    

    //Setteurs

    void setCell(Cell* i_cell);

    //Guetteurs
    Cell* getCell();
    RColor getColor() const;
};