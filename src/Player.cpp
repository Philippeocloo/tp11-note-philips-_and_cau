#include "Player.h"
#include "Robot.h"
#include "Board.h"
#include <iostream>
#include <unistd.h>

Player::Player(const char i_lettre)
    : m_lettre(i_lettre), m_points(0), m_buzzer(true),
      m_x(0), m_y(0), m_score(0), m_board(nullptr) {}

char Player::getLettre() const { return m_lettre; }
int Player::getPoints() const { return m_points; }
bool Player::getBuzzer() const { return m_buzzer; }
int Player::getX() const { return m_x; }
int Player::getY() const { return m_y; }
int Player::getScore() const { return m_score; }
Board* Player::getBoard() const {return m_board;}

void Player::setPoints(int i_points) { m_points = i_points; }
void Player::setBuzzer(bool i_buzzer) { m_buzzer = i_buzzer; }
void Player::setPosition(int i_x, int i_y) {
    m_x = i_x;
    m_y = i_y;
}
void Player::setScore(int i_score) { m_score = i_score; }

void Player::setTryBoard(Board* i_board) {
    m_board = new Board(*i_board); // Copie profonde
}

void Player::giveTry(Board* i_board, Robot* robot, Direction dir) {
    if (!robot || dir == Direction::NONE) {
        std::cout << "Aucune direction choisie.\n";
        return;
    }
    robot->move(dir, i_board);
}

bool Player::tryPlayer(Target i_target, Robot* i_robot, Direction i_dir, Robot* i_selectedRobot) {
    
    giveTry(m_board, i_selectedRobot, i_dir);

    if (i_robot->onTarget(i_target)) {
       std::cout << "Point !\n";
       return true;
    }
    return false;
}