#include "Player.h"
#include <iostream>

Player::Player(const std::string& i_lettre) : m_lettre(i_lettre), m_points(0), m_buzzer(true), x(0), y(0) {}

void Player::tryPlayer(int i_x, int i_y) {
    std::cout << "Le joueur " << m_lettre << " fait un essai en (" << m_x << ", " << m_y << ")." << std::endl;
    this->m_x = i_x;
    this->m_y = i_y;
}

std::string Player::getLettre() const {
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
