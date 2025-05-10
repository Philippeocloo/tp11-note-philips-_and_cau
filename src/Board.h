#pragma once

#include <vector>
#include "Cell.h"
#include "Robot.h"

#define TAILLE_X 16
#define TAILLE_Y 16

class Board {
    private:
        Cell cells[TAILLE_X][TAILLE_Y];
        std::vector<Robot> m_robots;
        std::vector<Target> m_allTargets;
        
    public:
        Board();

        Board(const Board& other);

        void initializeCells();
        void placeAngles();
        void initializeRobots();
        void printBoard() const;

        std::vector<Target>& getAllTargets() { return m_allTargets; };
        Cell& getCell(int x, int y) { return cells[x][y]; };
        const std::vector<Robot>* getRobots() const { return &m_robots; };

        void randomizeAnglesPosition(int dist_min, int dist_max, int& nex_index_on_axis);
        
};
