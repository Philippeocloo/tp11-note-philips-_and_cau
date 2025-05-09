#pragma once

#include <vector>
#include "Cell.h"
#include "Robot.h"
#include "Player.h"

#define TAILLE_X 16
#define TAILLE_Y 16

class Board {
    private:
        Cell cells[TAILLE_X][TAILLE_Y];
        std::vector<Robot> robots;
        std::vector<Player> players;
        
    public:
        Board();

        void initializeCells();
        void placeAngles();
        void initializeRobots();
        void initializePlayers();
        void printBoard() const;

        Cell& getCell(int x, int y) { return cells[x][y]; };
        const std::vector<Robot>* getRobots() const { return &robots; }; // Ajout de const
        const std::vector<Player>& getPlayers() const { return players; }; // Ajout de const

        void randomizeAnglesPosition(int dist_min, int dist_max, int& nex_index_on_axis);
        
};
