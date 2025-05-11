#include "GameSupervisor.h"


GameSupervisor::GameSupervisor(Board i_board ){
    // initialiser les membres et prendre en paramètre des noms de joueurs
    this->m_board = i_board;    
    this->m_targets_list = i_board.getAllTargets(); // initialiser la liste des cibles
}

void GameSupervisor::announceNb(Player* i_player,const int& i_number){
    this->m_announced_moves[i_player] = i_number;
    i_player->setBuzzer(false);
}

void GameSupervisor::initPlayers(std::string i_players_names){
    // initialiser les joueurs avec les noms donnés
    std::vector<Player> players;
    for (char name : i_players_names) {
        players.push_back(Player(name));
    }
    this->m_players = players;
}


void GameSupervisor::changeState(enum State i_actual_state){
    m_actual_state = i_actual_state;
    
    switch (i_actual_state) {
        
        case State::INIT_PLAYERS:
            std::cout << "Initialisation des joueurs" << std::endl;
            // remplir la liste de joueurs à partir de l'interface en appelant initPlayers(string i_players_names)
            break;

        case State::START_GAME:
            std::cout << "Début du jeu" << std::endl;
            break;

        case State::START_TOUR:
            std::cout << "Début du tour" << std::endl;
            // Choisir une cible aléatoire parmi la liste des cibles
            if (!m_targets_list.empty()) {
                int random_index = rand() % m_targets_list.size();
                this->m_current_target = m_targets_list[random_index];
            } else {
                std::cout << "Aucune cible disponible" << std::endl;
            }
            break;

        case State::WAIT_60SEC:
            std::cout << "Attente de 60 secondes" << std::endl;
            // A faire dans l'interface graphique :
            // Demarrer le timer de 60 secondes dans l'interface graphique
            break;

        case State::PLAYER_PROPOSAL:
            std::cout << "Proposition du joueur" << std::endl;
            // A faire dans l'interface graphique :
            // - passer dans cet état lorsque le joueur buzze
            // - Demander au joueur de faire une proposition
            // - Modifier la map m_announced_moves pour ajouter le joueur et son nombre de coups annoncés
            break;

        case State::END_60SEC:
            std::cout << "Fin des 60 secondes" << std::endl;
            sortPlayers(); // appel de la fonction sortPlayers
            // A faire dans l'interface graphique :
            // - Arrêter le timer de 60 secondes
            // - Passer à l'état START_PLAYER_PROPOSAL

            break;

        case State::START_PLAYER_PROPOSAL:
            std::cout << "Début de la proposition du joueur" << std::endl;
            m_real_movements_counter[m_sorted_players[0]] = 0; // initialiser le compteur de coups réels à 0
            m_sorted_players[0]->setTryBoard(&m_board); // mettre à jour le plateau du joueur

            // A faire dans l'interface graphique :
            // - Demander au joueur 0 dans le vecteur de joueur trié de choisir un robot et une direction
            // - Remplir la pair <robot, direction> avec les valeurs choisies
            // - Passer à l'état MOVING_ROBOT
            break;

        case State::MOVING_ROBOT:{
            std::cout << "Déplacement du robot" << std::endl; 
            
            //Mouvement du robot par le joueur
            bool on_target = m_sorted_players[0]->tryPlayer(
                m_current_target,
                findRobotByColor(m_board.getRobots(),m_current_target.getColor()), 
                m_robot_direction.second, 
                m_robot_direction.first); 
            
                m_real_movements_counter[m_sorted_players[0]]++; // incrémenter le compteur de coups réels

            if (on_target) {
                // Si le robot est sur la cible, donner un point au joueur
                givePoint(*m_sorted_players[0]);

                // Prendre le plateau du joueur et le mettre comme plateau de jeu
                this->m_board = *(m_sorted_players[0]->getBoard()); // mettre à jour le plateau du joueur

                //detruire la board du joueur
                delete m_sorted_players[0]->getBoard(); 

                //detruire la cible
                m_targets_list.erase(std::remove(m_targets_list.begin(), m_targets_list.end(), m_current_target), m_targets_list.end()); // enlever la cible de la liste des cibles

                // Passer à l'état END_TOUR 
                changeState(State::END_TOUR);

            } 
            else if(m_real_movements_counter[m_sorted_players[0]] >= m_announced_moves[m_sorted_players[0]]) {
                // Si le joueur a atteint le nombre de coups annoncés, passer à l'état END_PLAYER_PROPOSAL, il a raté son essai
                this->m_sorted_players.erase(this->m_sorted_players.begin()); // enlever le joueur qui vient de jouer
                // Passer à l'état END_PLAYER_PROPOSAL
                changeState(State::END_PLAYER_PROPOSAL);
            } 
            else {
                // Si le robot n'est pas sur la cible, passer à l'état START_PLAYER_PROPOSAL et redemander au joueur de choisir un robot et une direction
                // A faire dans l'interface graphique :*
                // - Demander au joueur de choisir un robot et une direction
                // - Remplir la pair <robot, direction> avec les valeurs choisies
                // - Passer à l'état MOVING_ROBOT
                
            }

            // A faire dans l'interface graphique :
            // - Déplacer le robot sur la carte

            break;
        }
        case State::END_PLAYER_PROPOSAL:{
            std::cout << "Fin de la proposition du joueur - Essai raté" << std::endl;
            if (m_sorted_players.size() > 1) {
                // Passer au joueur suivant
                m_sorted_players.erase(m_sorted_players.begin()); // enlever le joueur qui vient de jouer
                changeState(State::START_PLAYER_PROPOSAL); // passer à l'état START_PLAYER_PROPOSAL pour le joueur suivant
            } else {
                // Fin du tour
                changeState(State::END_TOUR);
            }
            // A faire dans l'interface graphique :
            // Rien
            break;
        }

        case State::END_TOUR:
            std::cout << "Fin du tour" << std::endl;
            // A faire dans l'interface graphique:
            // - Afficher les scores des joueurs
            // - Passer à l'état Start_Tour pour le prochain tour
            // - Si tous les tours sont terminés, passer à l'état END_GAME
            // - Prendre le board et le réinitialiser pour le prochain tour
            break;

        case State::END_GAME:
            std::cout << "Fin du jeu" << std::endl;
            break;

        default:
            std::cout << "État inconnu" << std::endl;
            break;  
    }
}

Robot* GameSupervisor::findRobotByColor(std::vector<Robot>* i_robots, const RColor& i_color) {
    for (Robot& robot : *i_robots) {
        if (robot.getColor() == i_color) {
            return &robot; // Retourner le robot trouvé
        }
    }
    // Si aucun robot n'est trouvé, afficher un message d'erreur
    std::cout<< "Robot non trouvé" << std::endl;
    return nullptr; // Retourner nullptr si le robot n'est pas trouvé
}

void GameSupervisor::givePoint(Player &i_player){ // ajouter un point au joueur gagnant
    int old_score = i_player.getScore();
    i_player.setScore(old_score++);
}

void GameSupervisor::sortPlayers() { // trier les joueurs en fonction de leur nombre de coups annoncés

    // vider le vecteur de joueurs triés
    this->m_sorted_players.clear(); 
    
    // Convertir la map en vecteur de paires pour le tri
    std::vector<std::pair<Player*, int>> vec(this->m_announced_moves.begin(), this->m_announced_moves.end());

    // Trier par valeur 
    std::sort(vec.begin(), vec.end(),
        [](const auto& a, const auto& b) { // fonction lambda pour comparer les nombres (élément 2 de chaque paire)
            return a.second < b.second;
        });

    // Extraire les joueurs dans un nouveau vecteur ordonné
    for (const auto& pair : vec) {
        this->m_sorted_players.push_back(pair.first);
    }

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

void  GameSupervisor::setCurrentTarget(const Target& i_current_target) { 
    this-> m_current_target = i_current_target; 
}

void  GameSupervisor::setTargetsList(const std::vector<Target>& i_targets_list) { 
    this-> m_targets_list = i_targets_list; 
}

void  GameSupervisor::setRobotDirection(const std::pair<Robot*, Direction>& i_robot_direction) { 
    this-> m_robot_direction = i_robot_direction; 
}

void  GameSupervisor::setSortedPlayers(const std::vector<Player*>& i_sorted_players) { 
    this-> m_sorted_players = i_sorted_players; 
}

void  GameSupervisor::setRealMovementsCounter(const std::map<Player*, int>& i_compteur_coups_reels) { 
    this-> m_real_movements_counter = i_compteur_coups_reels; 
}

void  GameSupervisor::setAnnouncedMoves(const std::map<Player*, int>& i_announced_moves) { 
    this-> m_announced_moves = i_announced_moves; 
}

// Getters
enum State GameSupervisor::getActualState() {
    return this-> m_actual_state;
}

Board GameSupervisor::getBoard() const { 
    return this-> m_board; 
}

std::vector<Player> GameSupervisor::getPlayers() const { 
    return this-> m_players; 
}

std::map<Player*, int> GameSupervisor::getAnnouncedMoves() const { 
    return this-> m_announced_moves; 
}

std::map<Player*, int> GameSupervisor::getRealMovementsCounter() const { 
    return this-> m_real_movements_counter; 
}

std::pair<Robot*, Direction> GameSupervisor::getRobotDirection() const { 
    return this-> m_robot_direction; 
}

std::vector<Player*> GameSupervisor::getSortedPlayers() const { 
    return this-> m_sorted_players; 
}


Target GameSupervisor::getCurrentTarget() const { 
    return this-> m_current_target; 
}

std::vector<Target> GameSupervisor::getTargetsList() const { 
    return this-> m_targets_list; 
}

