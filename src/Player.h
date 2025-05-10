#pragma once

#include <string>
#include "Target.h"
#include "enums/Direction.h"

class Board;
class Robot;

class Board;

class Player {
private:
    char m_lettre;
    int m_points;
    bool m_buzzer;
    int m_x;
    int m_y;
    int m_score;
    Board* m_board;

public:
    Player(const char lettre);
    
    void giveTry(Board* i_board, Robot* robot, Direction dir);

    bool tryPlayer(Target i_target, Robot* i_robot, Direction i_dir, Robot* i_selectedRobot);

    // Guetteurs
    char getLettre() const;
    int getPoints() const;
    bool getBuzzer() const;
    int getX() const;
    int getY() const;
    int getScore() const;
    Board* getBoard() const;

    void setPoints(int points);
    void setBuzzer(bool droit);
    void setTryBoard(Board* i_board);
    void setPosition(int x, int y);
    void setScore(int score);
};

