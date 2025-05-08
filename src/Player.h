#pragma once

#include <string>
#include "Target.h"
#include "enums/Direction.h"

struct MoveResult {
    Direction direction;
    int robotIndex;
};

class Board;

class Player {
private:
    char m_lettre;
    int m_points;
    bool m_buzzer;
    int m_x;
    int m_y;
    int m_score;

public:
    Player(const char lettre);

    //TODO: Je suis pas certain que ce soit le bon endroit pour ces fonctions (et elles empechent la compilation (interdépendance avec Board.h))
    /*
    MoveResult giveTry(Board* i_board, std::vector<Robot>& robots);
    bool tryPlayer(int i_tries, Target i_target, Board* i_board, std::vector<Robot>& robots);
    */
    

    // Guetteurs
    char getLettre() const;
    int getPoints() const;
    bool getBuzzer() const;
    int getX() const;
    int getY() const;
    int getScore() const;

    void setPoints(int points);
    void setBuzzer(bool droit);
    void setPosition(int x, int y);
    void setScore(int score);
};

