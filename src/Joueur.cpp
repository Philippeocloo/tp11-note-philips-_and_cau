#include "Joueur.h"
#include <iostream>

Joueur::Joueur(const std::string& lettre)
    : lettre(lettre), points(0), droit_buzzer(true), x(0), y(0) {}

void Joueur::essai(int x, int y) {
    std::cout << "Le joueur " << lettre << " fait un essai en (" << x << ", " << y << ")." << std::endl;
    this->x = x;
    this->y = y;
}

std::string Joueur::getLettre() const {
    return lettre;
}

int Joueur::getPoints() const {
    return points;
}

bool Joueur::getDroitBuzzer() const {
    return droit_buzzer;
}

int Joueur::getX() const {
    return x;
}

int Joueur::getY() const {
    return y;
}

void Joueur::setPoints(int points) {
    this->points = points;
}

void Joueur::setDroitBuzzer(bool droit) {
    droit_buzzer = droit;
}

void Joueur::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
