#pragma once

#include <vector>
#include "Cell.h"
#include "Robot.h"
#include "Player.h"

class Board {
    private:
        std::vector<Cell> cells;
        std::vector<Robot> robots;
        std::vector<Player> players;
        
        int const TAILLE_X = 16;
        int const TAILLE_Y = 16;
        
    public:
        Board();

        void initializeCells();
        void placeAngles(Board& i_board);
        void placeTargets();
        void initializeRobots(Board& i_board);
        void initializePlayers();
        void printBoard() const;

        std::vector<Cell>& getCases() { return cells; };
        const std::vector<Robot>& getRobots() const { return robots; }; // Ajout de const
        const std::vector<Player>& getPlayers() const { return players; }; // Ajout de const
};
