#include "GameSupervisor.h"


GameSupervisor::GameSupervisor(){
    // initialiser tous les membres et prendre en paramètre des noms de joueurs
}

void GameSupervisor::announceNb(Player& i_player,const int& i_number){
    this->m_announced_moves[i_player.getLettre()] = i_number;
    i_player.setBuzzer(false);
}

void GameSupervisor::announceAllNb(){
// do all process in first 60 secs
//à faire avec Yanis 
}

void GameSupervisor::new_tour(){
    announceAllNb();
    sort_players();

    for(auto &joueur : this-> m_players){ // parcourir la liste de joueur trié (le premier ayant le plus petit nb de moves)
        if(!joueur.getBuzzer()){ // si le joueur a donné son nb on lui laisse faire son essai
            joueur.setBuzzer(true); // redonner le droit de buzzer au joueur pour le prochain tour 
            if (joueur.tryPlayer()) {  // si il reussit il a un point en plus
                givePoint(joueur);
                return ; // on arrête le tour 
            }
        }
    }

}

void GameSupervisor::givePoint(Player &i_player){ // ajouete
    old_score = i_player.getScore();
    i_player.setScore(old_score++);
}

void GameSupervisor::sort_players(){ // trie tous le vecteur player selon l'ordre croissant des nbs donnés. Les derniers sont ceux qui n'ont pas donnés de nbs
    for ( auto & it : m_announced_moves){
        //creer un vecteur personne ordonées
    }
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
