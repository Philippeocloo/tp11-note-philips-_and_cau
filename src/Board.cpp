#include "Board.h"
#include <iostream>
#include <random>
#include <utility>

// Enum pour les quarts de plateau
enum Quarter {
    DOWN_LEFT   = 0,
    DOWN_RIGHT  = 1,
    UP_LEFT     = 2,
    UP_RIGHT    = 3
};

//-------------------------------TOOLS FUNCTIONS----------------------------------//
void randomize_angles_position(int dist_min, int dist_max, int& nex_index_on_axis) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(dist_min, dist_max);

    nex_index_on_axis = dist(rd);
}

void place_target(Board& board, int i_x, int i_y, std::vector<Target>& all_targets) {
    int i = rand() % all_targets.size();
    Target target = all_targets[i];
    i_board.getCases()[indexOfCase(i_board, i_x, i_y)].setTarget(target);

    all_targets.erase (all_targets.begin() + i);
}

int indexOfCase(Board& i_board, int x, int y) {
    for (int i = 0; i < i_board.getCases().size(); ++i) {
        if (i_board.getCases()[i].getX() == x && i_board.getCases()[i].getY() == y) {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------------//

//------------------------------PLATEAU------------------------------------//
Board::Board() {
    initialiser_joueurs();
    initialiser_robots(*this);
    initialiser_cases();
}

/***
 * @brief Initialise les cases du plateau
 * @details Les cases sont initialisées avec des coordonnées (x, y).
 *          Les cases sont ajoutées à la liste des cases du plateau.
 */
void Board::initialiser_cases() {
    for (int y = 0; y < TAILLE_Y; y++) {
        for (int x = 0; x < TAILLE_X; x++) {
            Case case_current(x, y);

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    Color color = static_cast<Color>(i);
                    Shape shape = static_cast<Shape>(j);
                    Target target(shape, color);
                    case_current.setTarget(target);
                }
            }
            cases.push_back(case_current);
        }
    }
}

void Board::place_angles(Board& i_board) {

    // Etape 1 : Création d'une liste de tous les symboles possibles sauf multicouleur
    std::vector<Target> all_targets; 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            all_targets.push_back(Target(static_cast<Shape>(i), static_cast<Color>(j)));
        }
    }
    
    Quarter quarter_of_board = Quarter::DOWN_LEFT;
    int x = 0;
    int y = 0;

    while (!all_targets.empty()) {

        switch (quarter_of_board) {
            case Quarter::DOWN_LEFT : 

                for (int i = 0; i < 4; i++) {
                    randomize_angles_position(0, 8, x);
                    randomize_angles_position(0, 8, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while (!(x == 0 && y == 0) || i_board.getCases()[indexOfCase(i_board, x, y)].hasTarget()) {
                            randomize_angles_position(0, 8, x);
                            randomize_angles_position(0, 8, y);
                    }
                    place_target(i_board, x, y, all_targets);
                }
                quarter_of_board = Quarter::DOWN_RIGHT; // On passe au quarter suivant
                break;

            case Quarter::DOWN_RIGHT : 

                for (int i = 0; i < 4; i++) {
                    randomize_angles_position(8, 16, x);
                    randomize_angles_position(0, 8, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while (!(x == 15 && y == 0) || i_board.getCases()[indexOfCase(i_board, x, y)].hasTarget()) {
                        randomize_angles_position(8, 16,x);
                        randomize_angles_position(0, 8, y);
                    }
                    place_target(i_board, x, y, all_targets);
                }
                quarter_of_board = Quarter::UP_LEFT;
                break;

            case Quarter::UP_LEFT: 

                for (int i = 0; i < 4; i++) {
                    randomize_angles_position(8, 16, x);
                    randomize_angles_position(0, 8, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while (!(x == 0 && y == 15) || i_board.getCases()[indexOfCase(i_board, x, y)].hasTarget()) {
                        randomize_angles_position(0, 8, x);
                        randomize_angles_position(8, 16, y);
                    }  
                    place_target(i_board, x, y, all_targets);
                }  
                quarter_of_board = Quarter::UP_RIGHT;
                break;

            case Quarter::UP_RIGHT: 

                for (int i = 0; i < 4; i++) {
                    randomize_angles_position(8, 16, x);
                    randomize_angles_position(0, 8, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while (!(x == 15 && y == 15) || i_board.getCases()[indexOfCase(i_board, x, y)].hasTarget()) {
                        randomize_angles_position(8, 16, x);
                        randomize_angles_position(8, 16, y);
                    }
                    place_target(i_board, x, y, all_targets);
                }
                break;
            
            default:
                std::cerr << "[Error] : Invalid Quarter with quarter = " << quarter_of_board << std::endl;
                return;
        }

    }
    randomize_angles_position(0, 16, x);
    randomize_angles_position(0, 16, y);
    while (!i_board.getCases()[indexOfCase(i_board, x, y)].hasTarget()) {
        randomize_angles_position(0, 16, x);
        randomize_angles_position(0, 16, y);
    }
    i_board.getCases()[indexOfCase(i_board, x, y)].setTarget(Target(Shape::CROSS, Color::MULTICOLOR));
}

/***
 * @brief Initialise les robots sur le i_board
 * @details Les robots sont initialisés avec des couleurs et des formes différentes.
 *          Les couleurs sont : RED, BLUE, YELLOW, GREEN
 *          Les formes sont : CROSS, CIRCLE, SQUARE
 * @note Les robots sont ajoutés à la liste des robots du i_board.
 */
void Board::initialiser_robots(Board& i_board) {

    int x = 0;
    int y = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Color color = static_cast<Color>(i);
            Shape shape = static_cast<Shape>(j);
            Robot robot(color, shape);

            while (i_board.getCases()[indexOfCase(i_board, x, y)].hasRobot()) {
                randomize_angles_position(0, 16, x);
                randomize_angles_position(0, 16, y);
        }
            robot.setPosition(0, 0); // Position initiale du robot
            robots.push_back(robot);
        }
    }
}

/***
 * @brief Initialise les joueurs sur le i_board
 * @details Les joueurs sont initialisés avec des identifiants de 0 à 3.
 *          Les joueurs sont ajoutés à la liste des joueurs du i_board.
 */
void Board::initialiser_joueurs() {
    for (int i = 0; i < 4; ++i) {
        Joueur joueur(i);
        joueurs.push_back(joueur);
    }
}

void Board::afficher_i_board() const {
    std::cout << "Board (" << TAILLE_X << " x " << TAILLE_Y << ")" << std::endl;
    for (int y = 0; y < TAILLE_Y; ++y) {
        for (int x = 0; x < TAILLE_X; ++x) {
            std::cout << ". ";
        }
        std::cout << std::endl;
    }
}
