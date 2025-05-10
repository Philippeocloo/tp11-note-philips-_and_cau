#include "Board.h"
#include "Cell.h"
#include "Robot.h"
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

/** 
    * @brief Teste si la case est contiguë à une bordure ou à un mur du plateau
    * @details La fonction vérifie si la case est sur le bord du plateau ou si elle est contiguë à une bordure.
    * @param i_x Coordonnée x de la case
    * @param i_y Coordonnée y de la case
    * @param i_board Pointeur vers le plateau
    * @return true Si la case est contiguë à une bordure ou à un mur du plateau
    * @return false Sinon
    */
bool testContiguousnessWithBorderOrBoardWall(int i_x, int i_y, Board* i_board) {
    if (i_x == 0 || i_x == TAILLE_X-1 || i_y == 0 || i_y == TAILLE_Y-1) {
        return true; // Si la case est sur le bord du plateau, elle ne peut pas être placée
    }
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i_board->getCell(i_x+i, i_y+j).getBorder() != Border::NONE) {
                return true; // Si la case voisine a une bordure, elle ne peut pas être placée
            }
        }
    }
    return false; // Si aucune case voisine n'a de bordure, elle peut être placée
}

/***
 * @brief Randomise la position d'un angle
 * @details La fonction génère un nombre aléatoire entre dist_min et dist_max pour la position d'un angle.
 * @param dist_min La distance minimale
 * @param dist_max La distance maximale
 * @param new_index_on_axis La nouvelle position de l'angle sur l'axe
 * @note Utilise std::random_device et std::uniform_int_distribution pour générer un nombre aléatoire
 */
void Board::randomizeAnglesPosition(int dist_min, int dist_max, int& new_index_on_axis) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(dist_min, dist_max);

    new_index_on_axis = dist(rd);
}

/***
 * @brief Place une cible sur le plateau
 * @details La fonction place une cible sur le plateau à la position (i_x, i_y) et l'enlève de la liste des cibles.
 * @param i_board Pointeur vers le plateau
 * @param i_x Coordonnée x de la case
 * @param i_y Coordonnée y de la case
 * @param m_allTargets Liste de toutes les cibles
 */
void placeTarget(Board* i_board, int i_x, int i_y, std::vector<Target>& m_allTargets) {
    int i = rand() % m_allTargets.size();
    Target target = m_allTargets[i];
    i_board->getCell(i_x,i_y).setTarget(target, true);

    m_allTargets.erase(m_allTargets.begin() + i);
}

/***
 * @brief Place une bordure sur le plateau
 * @details La fonction place une bordure sur le plateau à la position (i_x, i_y).
 * @param i_board Pointeur vers le plateau
 * @param i_x Coordonnée x de la case
 * @param i_y Coordonnée y de la case
 * @param i_border La bordure à placer
 */
void placeBorder(Board* i_board, int i_x, int i_y, Border i_border) {
    i_board->getCell(i_x,i_y).setBorder(i_border);
}

//---------------------------------------------------------------------------------//

//------------------------------PLATEAU------------------------------------//

/***
 * @brief Constructeur du plateau
 * @details Le constructeur initialise les joueurs, les m_robots et les cellules du plateau.
 */
Board::Board() {
    initializeCells();
    initializeRobots();
}

/***
 * @brief Constructeur de copie du plateau
 * @details Le constructeur copie les cellules, les m_robots et les joueurs de l'autre plateau.
 * @param other Le plateau à copier
 */
Board::Board(const Board& other) {
    for (int y = 0; y < TAILLE_Y; ++y) {
        for (int x = 0; x < TAILLE_X; ++x) {
            cells[x][y] = other.cells[x][y];
        }
    }
    m_robots = other.m_robots;
    m_allTargets = other.m_allTargets;
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
            cells[x][y] = cell_current;
            cells[x][y].setBorder(Border::NONE);
        }
    }
}

/***
 * @brief Place les angles sur le plateau
 * @details La fonction place les angles sur le plateau par quartiers.
 * @note Comme nous devons placer 17 symboles et 17 angles, chaque angle accueille un symbole 
 */
void Board::placeAngles() {

    // Etape 1 : Création d'une liste de tous les symboles possibles sauf multicouleur
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m_allTargets.push_back(Target(static_cast<Shape>(i), static_cast<RColor>(j)));
        }
    }
    
    Quarter quarter_of_board = Quarter::DOWN_LEFT;
    int x = 0;
    int y = 0;

    while (!m_allTargets.empty()) {

        switch (quarter_of_board) {
            case Quarter::DOWN_LEFT : 

                placeBorder(this, 7, 7, Border::SW); // Carré du middle

                for (int i = 0; i < 4; i++) {
                    randomizeAnglesPosition(0, 7, x);
                    randomizeAnglesPosition(0, 7, y);

                    // Vérifie si la cell un coin / est déjà occupée
                    while ((x == 0 && y == 0) 
                            || testContiguousnessWithBorderOrBoardWall(x, y, this)
                            || this->getCell(x,y).hasTarget()
                            || this->getCell(x,y).getBorder() != Border::NONE) {

                            randomizeAnglesPosition(0, 7, x);
                            randomizeAnglesPosition(0, 7, y);
                    }
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, m_allTargets);
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
                            || testContiguousnessWithBorderOrBoardWall(x, y, this)
                            || this->getCell(x,y).hasTarget()
                            || this->getCell(x,y).getBorder() != Border::NONE) {

                        randomizeAnglesPosition(8, 15, x);
                        randomizeAnglesPosition(0, 7, y);
                    }
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, m_allTargets);
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
                        || testContiguousnessWithBorderOrBoardWall(x, y, this)
                        || this->getCell(x,y).hasTarget()
                        || this->getCell(x,y).getBorder() != Border::NONE) {

                        randomizeAnglesPosition(0, 7, x);
                        randomizeAnglesPosition(8, 15, y);
                    }  
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, m_allTargets);
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
                        || testContiguousnessWithBorderOrBoardWall(x, y, this)
                        || this->getCell(x,y).hasTarget()
                        || this->getCell(x,y).getBorder() != Border::NONE) {
                        randomizeAnglesPosition(8, 15, x);
                        randomizeAnglesPosition(8, 15, y);
                    }
                    placeBorder(this, x, y, static_cast<Border>(i+1));
                    placeTarget(this, x, y, m_allTargets);
                }
                break;
            
            default:
                std::cerr << "[Error] : Invalid Quarter with quarter = " << quarter_of_board << std::endl;
                return;
        }

    }
    randomizeAnglesPosition(0, 15, x);
    randomizeAnglesPosition(0, 15, y);
    while ((x == 0 && y == 0) 
        || testContiguousnessWithBorderOrBoardWall(x, y, this)
        || (x == 15 && y == 15) 
        || this->getCell(x,y).hasTarget()) {
        randomizeAnglesPosition(0, 15, x);
        randomizeAnglesPosition(0, 15, y);
    }
    placeBorder(this, x, y, static_cast<Border>(rand() % 4 + 1));
    this->getCell(x,y).setTarget(Target(Shape::CROSS, RColor::MULTICOLOR), true);
}

/***
 * @brief Initialise les m_robots sur le i_board
 * @details Les m_robots sont initialisés avec des couleurs et des formes différentes.
 *          Les couleurs sont : RED, BLUE, YELLOW, GREEN
 *          Les formes sont : CROSS, CIRCLE, SQUARE
 * @note Les m_robots sont ajoutés à la liste des m_robots du this->
 */
void Board::initializeRobots() {

    int x = 0;
    int y = 0;

    for (int i = 0; i < 4; ++i) {
        
        RColor color = static_cast<RColor>(i);
        Robot robot(color, &cells[0][0]); // position temporaire
        randomizeAnglesPosition(0, 15, x);
        randomizeAnglesPosition(0, 15, y);
        
        // Choisir une case valide
        while (this->getCell(x,y).getBorder() != Border::NONE
            || this->getCell(x,y).hasRobot()) {
            randomizeAnglesPosition(0, 15, x);
            randomizeAnglesPosition(0, 15, y);
        }

        m_robots.push_back(robot); //On met le robot dans le vecteur
        
        m_robots.back().setCell(&cells[x][y]); 
        this->getCell(x,y).setRobot(&m_robots.back()); //On met le robot dans la case  

    }
}