#pragma once

#include <string>
#include "Target.h"
#include "enums/Direction.h"
#include "Board.h"
#include "Robot.h"

class Player {
private:
    char m_letter;
    bool m_buzzer;
    int m_score;
    Board* m_board;

public:

// Constructeur
    Player(const char letter);
    
// Getters
    char getLetter() const {return m_letter;};
    bool getBuzzer() const { return m_buzzer; };
    int  getScore() const { return m_score; };
    Board* getBoard() const { return m_board; };

//setters
    void setBuzzer(bool droit);
    void setScore(int score);
    void setTryBoard(Board* i_board) { m_board = i_board; };

// Autres méthodes
    void giveTry(Board* i_board, Robot* robot, Direction dir);
    bool tryPlayer(Target* i_target, Robot* i_robot, Direction i_dir, Robot* i_selectedRobot);
};

