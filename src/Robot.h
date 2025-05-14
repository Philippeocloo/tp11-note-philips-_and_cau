#pragma once

#include "enums/Color.h"
#include "enums/Direction.h"

class Cell;
class Board;
class Target;

/**
 * @class Robot
 * @brief Classe représentant un robot de couleur, capable de se déplacer sur un plateau.
 */
class Robot {
private:
    RColor m_color;
    Cell* m_cell;

public:

//Constructeurs
    /**
     * @brief Constructeur du Robot
     * @param i_couleur Couleur du robot
     * @param i_cell Cellule de départ du robot
     */
    Robot(RColor i_couleur, Cell* i_cell);

//Getters
/**
     * @brief Retourne la cellule actuelle du robot
     * @return Pointeur vers la cellule
     */
    Cell* getCell() const { return m_cell; };

    /**
     * @brief Retourne la couleur du robot
     * @return RColor Couleur du robot
     */
    RColor getColor() const {return m_color; };

//Setters
    /**
     * @brief Met à jour la cellule du robot
     * @param i_cell Nouvelle cellule à assigner au robot
     */
    void setCell(Cell* i_cell);

// Autres méthodes
    /**
     * @brief Vérifie si un obstacle empêche le robot de se déplacer dans une direction
     * @param dir Direction de déplacement souhaitée
     * @param i_board Plateau de jeu sur lequel est le robot
     * @return true si un obstacle est détecté, false sinon
     */
    bool checkIfObstacle(Direction dir, Board* i_board) ;

    /**
     * @brief Vérifie si le robot est positionné sur la cible donnée
     * @param i_target Pointeur vers la cible à vérifier
     * @return true si le robot est sur la cible, false sinon
     */
    bool onTarget(Target* i_target);

    /**
     * @brief Déplace le robot dans la direction indiquée tant qu'aucun obstacle n'est rencontré
     * @param i_direction Direction dans laquelle déplacer le robot
     * @param i_board Plateau de jeu utilisé pour le déplacement
     */
    void move(Direction i_direction, Board* i_board);
};