#include "Board.h"
#include "Cell.h"
#include "Target.h"
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
void Board::randomizeAnglesPosition(int dist_min, int dist_max, int& new_index_on_axis) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(dist_min, dist_max);

    new_index_on_axis = dist(rd);
}

void placeTarget(Board* i_board, int i_x, int i_y, std::vector<Target>& all_targets) {
    int i = rand() % all_targets.size();
    Target target = all_targets[i];
    i_board->getCell(i_x,i_y).setTarget(target);

    all_targets.erase(all_targets.begin() + i);
}

void placeBorder(Board* i_board, int i_x, int i_y, Border i_border) {
    i_board->getCell(i_x,i_y).setBorder(i_border);
}

//---------------------------------------------------------------------------------//

//------------------------------PLATEAU------------------------------------//
Board::Board() {
    initializePlayers();
    initializeRobots();
    initializeCells();
}

/***
 * @brief Initialise les cases du plateau
 * @details Les cases sont initialisées avec des coordonnées (x, y).
 *          Les cells sont ajoutées à la liste des cases du plateau.
 */
void Board::initializeCells() {
    for (int y = 0; y < TAILLE_Y; y++) {
        for (int x = 0; x < TAILLE_X; x++) {
            Cell cell_current(x, y);

            //TODO: Faulty logic 
            // for (int i = 0; i < 4; i++) {
            //     for (int j = 0; j < 4; j++) {
            //         RColor color = static_cast<RColor>(i);
            //         Shape shape = static_cast<Shape>(j);
            //         Target target(shape, color);
            //         cell_current.setTarget(target);
            //     }
            // }
            cells[x][y] = cell_current;
        }
    }
}

void Board::placeAngles() {

    // Etape 1 : Création d'une liste de tous les symboles possibles sauf multicouleur
    std::vector<Target> all_targets; 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            all_targets.push_back(Target(static_cast<Shape>(i), static_cast<RColor>(j)));
        }
    }
    
    Quarter quarter_of_board = Quarter::DOWN_LEFT;
    int x = 0;
    int y = 0;

    while (!all_targets.empty()) {

        switch (quarter_of_board) {
            case Quarter::DOWN_LEFT : 

                placeBorder(this, 7, 7, Border::SW); // Carré du middle

                for (int i = 0; i < 4; i++) {
                    randomizeAnglesPosition(0, 7, x);
                    randomizeAnglesPosition(0, 7, y);

                    // Vérifie si la cell un coin / est déjà occupée
                    while ((x == 0 && y == 0) 
                            || this->getCell(x,y).hasTarget()
                            || this->getCell(x,y).getBorder() != Border::NONE) {

                            randomizeAnglesPosition(0, 7, x);
                            randomizeAnglesPosition(0, 7, y);
                    }
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, all_targets);
                }
                quarter_of_board = Quarter::DOWN_RIGHT; // On passe au quarter suivant
                break;

            case Quarter::DOWN_RIGHT : 

                placeBorder(this, 8, 7, Border::SE); // Carré du middle

                for (int i = 0; i < 4; i++) {
                    randomizeAnglesPosition(8, 15, x);
                    randomizeAnglesPosition(0, 7, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while ((x == 15 && y == 0) 
                            || this->getCell(x,y).hasTarget()
                            || this->getCell(x,y).getBorder() != Border::NONE) {

                        randomizeAnglesPosition(8, 15, x);
                        randomizeAnglesPosition(0, 7, y);
                    }
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, all_targets);
                }
                quarter_of_board = Quarter::UP_LEFT;
                break;

            case Quarter::UP_LEFT: 

                placeBorder(this, 7, 8, Border::NW); // Carré du middle

                for (int i = 0; i < 4; i++) {
                    randomizeAnglesPosition(0, 7, x);
                    randomizeAnglesPosition(8, 15, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while ((x == 0 && y == 15) 
                        || this->getCell(x,y).hasTarget()
                        || this->getCell(x,y).getBorder() != Border::NONE) {

                        randomizeAnglesPosition(0, 7, x);
                        randomizeAnglesPosition(8, 15, y);
                    }  
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, all_targets);
                }  
                quarter_of_board = Quarter::UP_RIGHT;
                break;

            case Quarter::UP_RIGHT: 

                placeBorder(this, 8, 8, Border::NE); //Carré du middle

                for (int i = 0; i < 4; i++) {
                    randomizeAnglesPosition(8, 15, x);
                    randomizeAnglesPosition(8, 15, y);

                    // Vérifie si la case un coin / est déjà occupée
                    while ( (x == 15 && y == 15) 
                        || this->getCell(x,y).hasTarget()
                        || this->getCell(x,y).getBorder() != Border::NONE) {
                        randomizeAnglesPosition(8, 15, x);
                        randomizeAnglesPosition(8, 15, y);
                    }
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, all_targets);
                }
                break;
            
            default:
                std::cerr << "[Error] : Invalid Quarter with quarter = " << quarter_of_board << std::endl;
                return;
        }

    }
    randomizeAnglesPosition(0, 15, x);
    randomizeAnglesPosition(0, 15, y);
    while ((x == 0 && y == 0) || (x == 15 && y == 15) || this->getCell(x,y).hasTarget()) {
        randomizeAnglesPosition(0, 15, x);
        randomizeAnglesPosition(0, 15, y);
    }
    placeBorder(this, x, y, static_cast<Border>(rand() % 4 + 1));
    this->getCell(x,y).setTarget(Target(Shape::CROSS, RColor::MULTICOLOR));
}

/***
 * @brief Initialise les robots sur le i_board
 * @details Les robots sont initialisés avec des couleurs et des formes différentes.
 *          Les couleurs sont : RED, BLUE, YELLOW, GREEN
 *          Les formes sont : CROSS, CIRCLE, SQUARE
 * @note Les robots sont ajoutés à la liste des robots du this->
 */
void Board::initializeRobots() {

    int x = 0;
    int y = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            RColor color = static_cast<RColor>(i);
            Robot robot(color, &cells[0][0]); //Position initiale du Robot

            while (cells[x][y].hasRobot()) {
                randomizeAnglesPosition(0, 15, x);
                randomizeAnglesPosition(0, 15, y);
            }
            robots.push_back(robot);
        }
    }
}

/***
 * @brief Initialise les players sur le i_board
 * @details Les players sont initialisés avec des identifiants de 0 à 3.
 *          Les players sont ajoutés à la liste des players du this->
 */
void Board::initializePlayers() {
    for (int i = 0; i < 4; ++i) {
        Player player(i);
        players.push_back(player);
    }
}

void Board::printBoard() const {
    std::cout << "Board (" << TAILLE_X << " x " << TAILLE_Y << ")" << std::endl;
    for (int y = 0; y < TAILLE_Y; ++y) {
        for (int x = 0; x < TAILLE_X; ++x) {
            std::cout << ". ";
        }
        std::cout << std::endl;
    }
}
