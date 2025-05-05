#include "GameSupervisor.h"


GameSupervisor::GameSupervisor(){
    //init les targets de toutes les couleurs et toutes les shapes
}

void GameSupervisor::annonceNb(const Player& i_player,const int& i_number){
    this->m_announced_moves[i_player.getLettre()] = i_number
}

void GameSupervisor::new_tour(){
    //not finished
}


// Setters
void  GameSupervisor::setBoard(const Board& i_board) { 
    this-> m_board = i_board; 
}

void  GameSupervisor::setPlayers(const std::vector<Player>& i_player) { 
    this-> m_players = i_player; 
}

void  GameSupervisor::setCoupsAnnonces(const std::map<std::string, int>& i_announced_moves) { 
    this-> m_announced_moves = i_announced_moves; 
}

void  GameSupervisor::setCompteursCoupsReels(const std::map<std::string, int>& i_real_movements_counter) { 
    this-> m_real_movements_counter = i_real_movements_counter; 
}

void  GameSupervisor::setTargetCourante(const Target& i_current_target) { 
    this-> m_current_target = i_current_target; 
}

void  GameSupervisor::setListesTargets(const std::vector<Target>& i_targets_list) { 
    this-> m_targets_list = i_targets_list; 
}

// Getters
Board GameSupervisor::getBoard() const { 
    return this-> board; 
}

std::vector<Player> GameSupervisor::getPlayers() const { 
    return this-> players; 
}

std::map<std::string, int> GameSupervisor::getCoupsAnnonces() const { 
    return this-> announced_moves; 
}

std::map<std::string, int> GameSupervisor::getCompteursCoupsReels() const { 
    return this-> real_movements_counter; 
}

Target GameSupervisor::getTargetCourante() const { 
    return this-> current_target; 
}

std::vector<Target> GameSupervisor::getListesTargets() const { 
    return this-> targets_list; 
}
