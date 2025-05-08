#include "Player.h"
#include "Robot.h"
#include "Target.h"
#include <iostream>

#include <unistd.h>

Player::Player(const char i_lettre) : m_lettre(i_lettre), m_points(0), m_buzzer(true), m_x(0), m_y(0), m_score(0) {}


char Player::getLettre() const {
    return m_lettre;
}

int Player::getPoints() const {
    return m_points;
}

bool Player::getBuzzer() const {
    return m_buzzer;
}

int Player::getX() const {
    return m_x;
}

int Player::getY() const {
    return m_y;
}

int Player::getScore() const {
    return m_score;
}

void Player::setPoints(int i_points) {
    this->m_points = i_points;
}

void Player::setBuzzer(bool i_buzzer) {
    m_buzzer = i_buzzer;
}

void Player::setPosition(int i_x, int i_y) {
    this->m_x = i_x;
    this->m_y = i_y;
}

void Player::setScore(int i_score) {
    this->m_score = i_score;
}

// MoveResult Player::giveTry(Board* i_board, std::vector<Robot>& robots){

//      std::cout << "Choisis le numéro du robot : ";
//     int index;
//     std::cin >> index;
    
//     if (index < 0 || index >= (int)robots.size()) {
//         std::cout << "Indice invalide.\n";
//         return {Direction::NONE, -1};
//     }

//     Robot& selectedRobot = robots[index];

//     while (true) {
//         char first = 0;
//         if (first == 'x') return {Direction::NONE, index};

//         if (first == 27 && 0 == 91) {
//             char arrow = 0;
//             Direction dir = Direction::NONE;

//             switch (arrow) {
//                 case 'A': dir = Direction::UP; break;
//                 case 'B': dir = Direction::DOWN; break;
//                 case 'C': dir = Direction::RIGHT; break;
//                 case 'D': dir = Direction::LEFT; break;
//             }

//             if (dir != Direction::NONE) {
//                 selectedRobot.move(dir, i_board);
//                 std::cout << "Position : (" << selectedRobot.getCell()->getX()
//                           << ", " << selectedRobot.getCell()->getY() << ")\n";
//                 return {dir, index};
//             }
//         }
//     }
// }

// bool Player::tryPlayer(int i_tries, Target i_target, Board* i_board, std::vector<Robot>& robots) {
//     while (i_tries > 0) {
//         std::cout << "\nMouvements restants : " << i_tries << std::endl;

//         MoveResult result = giveTry(i_board, robots);
//         if (result.direction == Direction::NONE || result.robotIndex == -1) {
//             std::cout << "Loose\n";
//             return false;
//         }

//         if (robots[result.robotIndex].onTarget(i_target)) {
//             std::cout << "Point !\n";
//             return true;
//         }

//         i_tries--;
//     }

//     std::cout << "Loose\n";
//     return false;
// }