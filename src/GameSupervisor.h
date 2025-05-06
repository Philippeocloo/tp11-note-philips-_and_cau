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
    Board m_board ;
    std::vector<Player> m_players;
    std::map<Player , int> m_announced_moves;
    std::map<Player , int> m_real_movements_counter;
    Target m_current_target; 
    std::vector<Target> m_targets_list;

public:
//    GameSupervisor();

    GameSupervisor(std::vector<Player> i_players,Board i_board );

    void newTour();

    void announceNb(Player i_player,int i_number);

    void announceAllNb();

    void givePoint(Player & i_player);

    std::vector<Player> sortPlayers();

    // Setters
    void  setBoard(const Board& i_board);

    void  setPlayers(const std::vector<Player>& i_player);

    void  setCoupsAnnonces(const std::map<Player, int>& i_announced_moves);

    void  setCompteursCoupsReels(const std::map<Player, int>& i_real_movements_counter);

    void  setTargetCourante(const Target& i_current_target);

    void  setListesTargets(const std::vector<Target>& i_targets_list);

    // Getters
    Board getBoard() const;

    std::vector<Player> getPlayers() const;
    
    std::map<Player, int> getCoupsAnnonces() const;
    
    std::map<Player, int> getCompteursCoupsReels() const;
    
    Target getTargetCourante() const;
    
    std::vector<Target> getListesTargets() const;
    
};