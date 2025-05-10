#pragma once

#include "Board.h"
#include "Player.h"
#include "Target.h"
#include "Robot.h"
#include "enums/State.h"

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <iostream>

class GameSupervisor{

private : 
    // Attributs
    Board m_board ;
    std::vector<Player> m_players;
    std::map<Player* , int> m_announced_moves;
    std::map<Player* , int> m_real_movements_counter;
    std::pair<Robot*, Direction> m_robot_direction;
    std::vector<Player*> m_sorted_players;
    Target m_current_target; 
    std::vector<Target> m_targets_list;
    enum State m_actual_state = State::INIT_PLAYERS;

public:

    GameSupervisor(Board i_board);

    void initPlayers(std::string i_players_names);

    void announceNb(Player* i_player,const int& i_number);

    void changeState(enum State i_actual_state);

    void givePoint(Player & i_player);

    void sortPlayers();

    Robot* findRobotByColor(std::vector<Robot>* i_robots, const RColor& i_color);


    // Setters
    void  setActualState(const enum State& i_actual_state);

    void  setBoard(const Board& i_board);

    void  setPlayers(const std::vector<Player>& i_player);

    void  setCurrentTarget(const Target& i_current_target);

    void  setRobotDirection(const std::pair<Robot*, Direction>& i_robot_direction);

    void  setSortedPlayers(const std::vector<Player*>& i_sorted_players);

    void  setRealMovementsCounter(const std::map<Player*, int>& i_compteur_coups_reels);

    void  setAnnouncedMoves(const std::map<Player*, int>& i_announced_moves);

    void  setTargetsList(const std::vector<Target>& i_targets_list);

    // Getters

    enum State getActualState();

    Board getBoard() const;

    std::vector<Player> getPlayers() const;
    
    std::map<Player*, int> getAnnouncedMoves() const;
    
    std::map<Player*, int> getRealMovementsCounter() const;

    std::pair<Robot*, Direction> getRobotDirection() const;

    std::vector<Player*> getSortedPlayers() const;
    
    Target getCurrentTarget() const;
    
    std::vector<Target> getTargetsList() const;
    
};