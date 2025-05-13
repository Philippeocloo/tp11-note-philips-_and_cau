#include "Player.h"
#include "Robot.h"
#include "Board.h"
#include <iostream>
#include <unistd.h>

//--------------CONSTRUCTEUR------------------//
Player::Player(const char i_letter) : 
    m_letter(i_letter), 
    m_buzzer(true),
    m_score(0)
    {}
//____________________________________________//

//--------------SETTERS-----------------------//
void Player::setBuzzer(bool i_buzzer) { 
    m_buzzer = i_buzzer; 
}

void Player::setScore(int i_score) { 
    m_score = i_score; 
}
//____________________________________________//

//--------------AUTRES METHODES-----------------------//
void Player::giveTry(Board* i_board, Robot* robot, Direction dir) {
    if (!robot || dir == Direction::NONE) {
        std::cout << "Aucune direction choisie.\n";
        return;
    }
    robot->move(dir, i_board);
}

bool Player::tryPlayer(
    Target* i_target, 
    Robot* i_robot, 
    Direction i_dir, 
    Robot* i_selectedRobot
    ) {
    
    giveTry(m_board, i_selectedRobot, i_dir);

    if (i_robot->onTarget(i_target)) {
       std::cout << "Point !\n";
       return true;
    }
    return false;
}