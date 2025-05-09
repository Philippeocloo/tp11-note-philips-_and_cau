#pragma once

#include "Board.h"
#include "Player.h"
#include "Target.h"
#include "Robot.h"

#include <vector>
#include <map>
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
    Target m_current_target; 
    std::vector<Target> m_targets_list;
    enum State m_actual_state = State::INIT_PLAYERS;

public:

    GameSupervisor(Board i_board);

    void playersTrials();

    void initPlayers(string i_players_names);

    void announceNb(Player* i_player,const int& i_number);

    void changeState(enum State i_actual_state);

    void givePoint(Player & i_player);

    std::vector<Player*> sortPlayers();

    // Setters
    void  setBoard(const Board& i_board);

    void  setPlayers(const std::vector<Player>& i_player);

    void  setTargetCourante(const Target& i_current_target);

    void  setListesTargets(const std::vector<Target>& i_targets_list);

    // Getters

    enum State getActualState() const;

    Board getBoard() const;

    std::vector<Player> getPlayers() const;
    
    std::map<Player*, int> getCoupsAnnonces() const;
    
    std::map<Player*, int> getCompteursCoupsReels() const;
    
    Target getTargetCourante() const;
    
    std::vector<Target> getListesTargets() const;
    
};