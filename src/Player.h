#pragma once

/**
 * @file Player.h
 * @brief Déclaration de la classe Player représentant un joueur du jeu.
 */

#include <string>
#include "Target.h"
#include "enums/Direction.h"
#include "Board.h"
#include "Robot.h"

/**
 * @class Player
 * @brief Classe représentant un joueur, avec sa lettre, son score, son plateau temporaire, etc.
 */
class Player {
private:
    char m_letter;
    bool m_buzzer;
    int m_score;
    Board* m_board;

public:

// Constructeur
    /**
     * @brief Constructeur de la classe Player
     * @param letter Lettre identifiant le joueur
     */
    Player(const char letter);
    
// Getters
    
    /** @brief Retourne la lettre identifiant le joueur */
    char getLetter() const { return m_letter; };

    /** @brief Indique si le joueur peut buzzer */
    bool getBuzzer() const { return m_buzzer; };

    /** @brief Retourne le score du joueur */
    int getScore() const { return m_score; };

    /** @brief Retourne le plateau temporaire associé au joueur */
    Board* getBoard() const { return m_board; };

//setters
    /**
     * @brief Active ou désactive le buzzer du joueur
     * @param droit true si le joueur peut buzzer, false sinon
     */
    void setBuzzer(bool droit);

    /**
     * @brief Met à jour le score du joueur
     * @param score Nouveau score à attribuer
     */
    void setScore(int score);

    /**
     * @brief Définit le plateau temporaire du joueur
     * @param i_board Pointeur vers le plateau de test
     */
    void setTryBoard(Board* i_board) { m_board = i_board; };

// Autres méthodes
    /**
     * @brief Effectue un déplacement d’un robot sur un plateau
     * @param i_board Plateau sur lequel déplacer le robot
     * @param robot Robot à déplacer
     * @param dir Direction dans laquelle déplacer le robot
     */
    void giveTry(Board* i_board, Robot* robot, Direction dir);

    /**
     * @brief Tente une action de jeu : déplacement + vérification si le robot atteint la cible
     * @param i_target Cible à atteindre
     * @param i_robot Robot lié à la cible (peut être nullptr)
     * @param i_dir Direction choisie
     * @param i_selectedRobot Robot effectivement sélectionné par le joueur
     * @return true si la cible est atteinte, false sinon
     */
    bool tryPlayer(Target* i_target, Robot* i_robot, Direction i_dir, Robot* i_selectedRobot);
};

