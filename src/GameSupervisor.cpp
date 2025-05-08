#include "GameSupervisor.h"


GameSupervisor::GameSupervisor(std::vector<Player> i_players,Board i_board ){
    // initialiser les membres et prendre en paramètre des noms de joueurs
    this->m_players = i_players;
    this->m_board = i_board;    
}

void GameSupervisor::announceNb(Player* i_player,const int& i_number){
    this->m_announced_moves[i_player] = i_number;
    i_player->setBuzzer(false);
}

void GameSupervisor::announceAllNb(){
// do all process in first 60 secs
//à faire avec Yanis (dépendant de la partie graphique)
}

void GameSupervisor::newTour(){

    announceAllNb(); // premieres 60 sec

    std::vector<Player*> sorted_players = sortPlayers();

    for(Player* joueur : sorted_players){ // parcourir la liste de joueur trié (le premier ayant le plus petit nb de moves)
            joueur->setBuzzer(true); // redonner le droit de buzzer au joueur pour le prochain tour 

            //TODO: En rediscuter (voir Player.h:26)
            // if (joueur.tryPlayer()) {  // si il reussit il a un point en plus
            //     givePoint(joueur);
            //     return ; // on arrête le tour sinon on continue avec les autres joueurs
            // }
    }

    return;
}

void GameSupervisor::givePoint(Player &i_player){ // ajouter un point au joueur gagnant
    int old_score = i_player.getScore();
    i_player.setScore(old_score++);
}

std::vector<Player*> GameSupervisor::sortPlayers() { // trier les joueurs en fonction de leur nombre de coups annoncés

    // Convertir la map en vecteur de paires pour le tri
    std::vector<std::pair<Player*, int>> vec(this->m_announced_moves.begin(), this->m_announced_moves.end());

    // Trier par valeur 
    std::sort(vec.begin(), vec.end(),
        [](const auto& a, const auto& b) { // fonction lambda pour comparer les nombres (élément 2 chaque paire)
            return a.second < b.second;
        });

    // Extraire les joueurs dans un nouveau vecteur ordonné
    std::vector<Player*> sorted_players;

    for (const auto& pair : vec) {
        sorted_players.push_back(pair.first);
    }

    return sorted_players;

}

// Setters
void  GameSupervisor::setBoard(const Board& i_board) { 
    this-> m_board = i_board; 
}

void  GameSupervisor::setPlayers(const std::vector<Player>& i_player) { 
    this-> m_players = i_player; 
}

void  GameSupervisor::setTargetCourante(const Target& i_current_target) { 
    this-> m_current_target = i_current_target; 
}

void  GameSupervisor::setListesTargets(const std::vector<Target>& i_targets_list) { 
    this-> m_targets_list = i_targets_list; 
}

// Getters
Board GameSupervisor::getBoard() const { 
    return this-> m_board; 
}

std::vector<Player> GameSupervisor::getPlayers() const { 
    return this-> m_players; 
}

std::map<Player*, int> GameSupervisor::getCoupsAnnonces() const { 
    return this-> m_announced_moves; 
}

std::map<Player*, int> GameSupervisor::getCompteursCoupsReels() const { 
    return this-> m_real_movements_counter; 
}

Target GameSupervisor::getTargetCourante() const { 
    return this-> m_current_target; 
}

std::vector<Target> GameSupervisor::getListesTargets() const { 
    return this-> m_targets_list; 
}
