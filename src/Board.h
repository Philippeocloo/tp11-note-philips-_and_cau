#pragma once

#include <vector>
#include "Case.h"
#include "Robot.h"
#include "Joueur.h"

class Board {
    private:
        std::vector<Case> cases;
        std::vector<Robot> robots;
        std::vector<Joueur> joueurs;
        
        int const TAILLE_X = 16;
        int const TAILLE_Y = 16;
        
    public:
        Board();

        void initialiser_cases();
        void place_angles(Board& i_board);
        void place_targets();
        void initialiser_robots(Board& i_board);
        void initialiser_joueurs();
        void afficher_i_board() const;

        std::vector<Case>& getCases() { return cases; };
        const std::vector<Robot>& getRobots() const { return robots; }; // Ajout de const
        const std::vector<Joueur>& getJoueurs() const { return joueurs; }; // Ajout de const
};
