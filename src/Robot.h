#pragma once

#include "enums/Color.h"
#include "enums/Color.h"
#include "enums/Direction.h"
#include "Cell.h"
#include "Target.h"


class Robot {
private:
    Color m_color;
    Cell m_cell;

public:
    Robot(Color i_couleur, Cell i_cell);
    bool checkifobstacle(Direction dir,Board& i_board);
    bool onTarget(Target i_target);
    void move(Direction i_direction, Board& i_board);
    

    //Setteurs

    void setCell(Cell& i_cell);

    //Guetteurs
    Cell getCell();
    Color getCouleur() const;
};