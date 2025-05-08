#pragma once

#include <string>
#include "Target.h"
#include "Board.h"
#include "enums/Direction.h"

struct MoveResult {
    Direction direction;
    int robotIndex;
};

class Board;

class Player {
private:
    std::string m_lettre;
    int m_points;
    bool m_buzzer;
    int m_x;
    int m_y;
    int m_score;

public:
    Player(const std::string& lettre);

    MoveResult giveTry(Board* i_board, std::vector<Robot>& robots);
    bool tryPlayer(int i_tries, Target i_target, Board* i_board, std::vector<Robot>& robots);

    // Guetteurs
    std::string getLettre() const;
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

