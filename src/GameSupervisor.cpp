#include "GameSupervisor.h"


GameSupervisor::GameSupervisor(Board i_board ){
    // initialiser les membres et prendre en paramètre des noms de joueurs
    this->m_board = i_board;    
}

void GameSupervisor::announceNb(Player* i_player,const int& i_number){
    this->m_announced_moves[i_player] = i_number;
    i_player->setBuzzer(false);
}

void GameSupervisor::initPlayers(string i_players_names){
    // initialiser les joueurs avec les noms donnés
    std::vector<Player> players;
    for (char name : i_players_names) {
        players.push_back(Player(name));
    }
    this->m_players = players;
}


void GameSupervisor::changeState(enum State i_actual_state){
    m_actual_state = i_actual_state;
    
    switch (m_actual_state) {
        
        case INIT_PLAYERS:
            std::cout << "Initialisation des joueurs" << std::endl;
            break;

        case START_GAME:
            std::cout << "Début du jeu" << std::endl;
            break;

        case START_TOUR:
            std::cout << "Début du tour" << std::endl;
            break;

        case WAIT_60SEC:
            std::cout << "Attente de 60 secondes" << std::endl;
            break;

        case PLAYER_PROPOSAL:
            std::cout << "Proposition du joueur" << std::endl;
            break;

        case END_60SEC:
            std::cout << "Fin des 60 secondes" << std::endl;
            break;

        case PLAYERS_TRIALS:
            std::cout << "Essais des joueurs" << std::endl;
            playersTrials(); // appel de la fonction newTour
            break;

        case END_TOUR:
            std::cout << "Fin du tour" << std::endl;
            break;

        case END_GAME:
            std::cout << "Fin du jeu" << std::endl;
            break;

        default:
            std::cout << "État inconnu" << std::endl;
            break;  
    }
}


void GameSupervisor::playersTrials(){

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
        [](const auto& a, const auto& b) { // fonction lambda pour comparer les nombres (élément 2 de chaque paire)
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

void GameSupervisor::setActualState(const enum State& i_actual_state){
    this-> m_actual_state = i_actual_state;
}

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
enum State getActualState() const {
    return this-> m_actual_state;
}

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

