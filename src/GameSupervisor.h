#pragma once

#include "Board.h"
#include "Player.h"
#include "Target.h"
#include "Robot.h"

#include <vector>
#include <map>
#include <string>

class GameSupervisor{

private : 
    Board m_board ;
    std::vector<Player> m_players;
    std::map<std::string , int> m_announced_moves;
    std::map<std::string , int> m_real_movements_counter;
    Target m_current_target; 
    std::vector<Target> m_targets_list;

public:
    GameSupervisor();

    new_tour();

    annonceNb(Player i_player,int i_number);

    move(Robot i_robot, String i_direction);

    bool test_target_reached() const;


    // Setters
    void  setBoard(const Board& i_board);

    void  setPlayers(const std::vector<Player>& i_player);

    void  setCoupsAnnonces(const std::map<std::string, int>& i_announced_moves);

    void  setCompteursCoupsReels(const std::map<std::string, int>& i_real_movements_counter);

    void  setTargetCourante(const Target& i_current_target);

    void  setListesTargets(const std::vector<Target>& i_targets_list);


    // Getters
    Board getBoard() const;
    std::vector<Player> getPlayers() const;
    std::map<std::string, int> getCoupsAnnonces() const;
    std::map<std::string, int> getCompteursCoupsReels() const;
    Target getTargetCourante() const;
    std::vector<Target> getListesTargets() const;
    
};