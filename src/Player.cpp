#include "Player.h"
#include "Robot.h"
#include "Board.h"
#include <iostream>
#include <unistd.h>

//--------------CONSTRUCTEUR------------------//
/**
 * @brief Constructeur du joueur
 * @param i_letter Lettre identifiant le joueur (ex: 'A', 'B'…)
 */
Player::Player(const char i_letter) : 
    m_letter(i_letter), 
    m_buzzer(true),
    m_score(0)
    {}
//____________________________________________//

//--------------SETTERS-----------------------//
/**
 * @brief Définit l’état du buzzer du joueur
 * @param i_buzzer true si le joueur peut buzzer, false sinon
 */
void Player::setBuzzer(bool i_buzzer) { 
    m_buzzer = i_buzzer; 
}

/**
 * @brief Définit le score du joueur
 * @param i_score Score à attribuer
 */
void Player::setScore(int i_score) { 
    m_score = i_score; 
}
//____________________________________________//

//--------------AUTRES METHODES-----------------------//
/**
 * @brief Effectue un déplacement d’un robot dans une direction
 * @param i_board Pointeur vers le plateau de jeu
 * @param robot Pointeur vers le robot à déplacer
 * @param dir Direction dans laquelle déplacer le robot
 */
void Player::giveTry(Board* i_board, Robot* robot, Direction dir) {
    if (!robot || dir == Direction::NONE) {
        std::cout << "Aucune direction choisie.\n";
        return;
    }
    robot->move(dir, i_board);
}

/**
 * @brief Tente une action de jeu : déplacement + vérification de cible
 * @details Le joueur tente de déplacer un robot et vérifie si celui-ci atteint la cible.
 * @param i_target Pointeur vers la cible visée
 * @param i_robot Pointeur vers le robot associé à la cible (peut être nullptr)
 * @param i_dir Direction à utiliser pour le mouvement
 * @param i_selectedRobot Pointeur vers le robot réellement sélectionné par le joueur
 * @return true si la cible est atteinte après le déplacement, false sinon
 */
bool Player::tryPlayer(
    Target* i_target, 
    Robot* i_robot, 
    Direction i_dir, 
    Robot* i_selectedRobot
    ) {
    
    giveTry(m_board, i_selectedRobot, i_dir);

    if(i_robot != nullptr) {
        if (i_robot->onTarget(i_target)) {
            std::cout << "Point !\n";
            return true;
        }
    } else {
        if (i_selectedRobot->onTarget(i_target)) {
            std::cout << "Point !\n";
            return true;
        }
    }

    
    return false;
}