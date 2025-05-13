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

// Constructeurs
        Board();
        Board(const Board& other); // Constructeur de copie

// Destructeur
        ~Board() = default;

// Getters
        std::vector<Target>&    getAllTargets() { return m_allTargets; };
        Cell&                   getCell(int x, int y) { return cells[x][y]; };
        std::vector<Robot>*     getRobots() { return &m_robots; };

// Autres méthodes
        void initializeCells();
        void placeAngles();
        void initializeRobots();
        void randomizeAnglesPosition(int dist_min, int dist_max, int& nex_index_on_axis);
        
};
