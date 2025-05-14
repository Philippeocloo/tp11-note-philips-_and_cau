#include "GameSupervisor.h"

/**
 * @file GameSupervisor.cpp
 * @brief Implémente la logique de gestion du jeu : état, transitions, tri des joueurs, attribution des points, etc.
 */

/**
 * @brief Constructeur du GameSupervisor
 * Initialise un nouveau plateau, place les cibles et récupère la liste des cibles.
 */
GameSupervisor::GameSupervisor()
{
    m_board = new Board();
    m_board->placeAngles();
    m_targets_list = m_board->getAllTargets();
}

/**
 * @brief Enregistre le nombre de coups annoncés par un joueur
 * @param i_player Pointeur vers le joueur
 * @param i_number Nombre de coups annoncés
 */
void GameSupervisor::announceNb(Player* i_player,const int& i_number){
    this->m_announced_moves[i_player] = i_number;
    i_player->setBuzzer(false);
}

/**
 * @brief Initialise les joueurs à partir d'une chaîne de caractères contenant leurs noms
 * @param i_players_names Chaîne contenant les noms des joueurs (ex: "ABCD")
 */
void GameSupervisor::initPlayers(std::string i_players_names){
    // initialiser les joueurs avec les noms donnés
    std::vector<Player> players;
    for (char name : i_players_names) {
        players.push_back(Player(name));
    }
    this->m_players = players;
}

/**
 * @brief Gère le changement d'état du jeu
 * @param i_actual_state Nouvel état à appliquer
 */
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
            if (!m_targets_list->empty()) {
                int random_index = rand() % m_targets_list->size();
                this->m_current_target = (*m_targets_list)[random_index];
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
            m_sorted_players[0]->setTryBoard(new Board(*m_board)); // mettre à jour le plateau du joueur

            // A faire dans l'interface graphique :
            // - Passer à l'état WAIT_FOR_MOVE
            break;
        case State::WAIT_FOR_MOVE:
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
                nullptr, 
                m_robot_direction.second, 
                m_robot_direction.first); 
            
                m_real_movements_counter[m_sorted_players[0]]++; // incrémenter le compteur de coups réels

            if (on_target) {
                // Si le robot est sur la cible, donner un point au joueur
                givePoint(*m_sorted_players[0]);
                delete this->m_board;
                // Prendre le plateau du joueur et le mettre comme plateau de jeu
                this->m_board = new Board(*m_sorted_players[0]->getBoard()); // mettre à jour le plateau du joueur

                 

                unsigned int indexToDelete = 255;
                //detruire la cible
                for (unsigned int i = 0; i < m_targets_list->size(); i++)
                {
                    Target* t = (*m_targets_list)[i];
                    if(t == m_current_target) {
                        delete t;
                        indexToDelete = i;
                    }
                }
                m_targets_list->erase(m_targets_list->begin()+indexToDelete);
                //m_targets_list->erase(std::remove(m_targets_list->begin(), m_targets_list->end(), m_current_target), m_targets_list->end()); // enlever la cible de la liste des cibles

                delete &m_current_target;

                //detruire la board du joueur
                delete m_sorted_players[0]->getBoard();

                // Passer à l'état END_TOUR 
                changeState(State::END_TOUR);

            } 
            else if(m_real_movements_counter[m_sorted_players[0]] >= m_announced_moves[m_sorted_players[0]]) {
                // Si le joueur a atteint le nombre de coups annoncés, passer à l'état END_PLAYER_PROPOSAL, il a raté son essai
                // Passer à l'état END_PLAYER_PROPOSAL
                changeState(State::END_PLAYER_PROPOSAL);
            } 
            else {
                // Si le robot n'est pas sur la cible, passer à l'état START_PLAYER_PROPOSAL et redemander au joueur de choisir un robot et une direction
                changeState(State::WAIT_FOR_MOVE);
            }

            // A faire dans l'interface graphique :
            // - Déplacer le robot sur la carte

            break;
        }
        case State::END_PLAYER_PROPOSAL:{
            std::cout << "Fin de la proposition du joueur - Essai raté" << std::endl;
            if (m_sorted_players.size() > 1) {
                // Passer au joueur suivant
                delete (m_sorted_players[0]->getBoard());
                m_sorted_players[0]->setTryBoard(nullptr);
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
            break;

        case State::END_GAME:
            std::cout << "Fin du jeu" << std::endl;
            break;

        default:
            std::cout << "État inconnu" << std::endl;
            break;  
    }
}

/**
 * @brief Trouve un robot selon sa couleur
 * @param i_robots Vecteur de robots
 * @param i_color Couleur recherchée
 * @return Pointeur vers le robot correspondant ou nullptr s'il n'existe pas
 */
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

/**
 * @brief Donne un point à un joueur
 * @param i_player Référence vers le joueur à qui ajouter un point
 */
void GameSupervisor::givePoint(Player &i_player){ // ajouter un point au joueur gagnant
    int old_score = i_player.getScore();
    i_player.setScore(old_score+1);
}

/**
 * @brief Trie les joueurs par ordre croissant du nombre de coups annoncés
 */
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
/** @brief Définit l'état actuel du jeu */
void GameSupervisor::setActualState(const enum State& i_actual_state){
    this-> m_actual_state = i_actual_state;
}

/** @brief Définit la liste des joueurs */
void  GameSupervisor::setPlayers(const std::vector<Player>& i_player) { 
    this-> m_players = i_player; 
}

/** @brief Définit la cible actuelle */
void  GameSupervisor::setCurrentTarget(Target* i_current_target) { 
    this-> m_current_target = i_current_target; 
}

/** @brief Définit la liste des cibles */
void  GameSupervisor::setTargetsList(std::vector<Target*>* i_targets_list) { 
    this-> m_targets_list = i_targets_list; 
}

/** @brief Définit la direction et le robot choisis par le joueur */
void  GameSupervisor::setRobotDirection(const std::pair<Robot*, Direction>& i_robot_direction) { 
    this-> m_robot_direction = i_robot_direction; 
}

/** @brief Définit la liste triée des joueurs pour le tour courant */
void  GameSupervisor::setSortedPlayers(const std::vector<Player*>& i_sorted_players) { 
    this-> m_sorted_players = i_sorted_players; 
}

/** @brief Définit le compteur de coups réels des joueurs */
void  GameSupervisor::setRealMovementsCounter(const std::map<Player*, int>& i_compteur_coups_reels) { 
    this-> m_real_movements_counter = i_compteur_coups_reels; 
}

/** @brief Définit le nombre de coups annoncés par les joueurs */
void  GameSupervisor::setAnnouncedMoves(const std::map<Player*, int>& i_announced_moves) { 
    this-> m_announced_moves = i_announced_moves; 
}

// Getters
/** @brief Retourne l'état actuel du jeu */
enum State GameSupervisor::getActualState() {
    return this-> m_actual_state;
}

/** @brief Retourne un pointeur vers le plateau */
Board* GameSupervisor::getBoard() { 
    return this-> m_board; 
}

/** @brief Retourne une référence vers la liste des joueurs */
std::vector<Player>& GameSupervisor::getPlayers() { 
    return this-> m_players; 
}

/** @brief Retourne une référence vers la map des coups annoncés */
std::map<Player*, int>& GameSupervisor::getAnnouncedMoves() { 
    return this-> m_announced_moves; 
}

/** @brief Retourne une référence vers la map des coups réellement joués */
std::map<Player*, int>& GameSupervisor::getRealMovementsCounter() { 
    return this-> m_real_movements_counter; 
}

/** @brief Retourne la paire (robot, direction) courante */
std::pair<Robot*, Direction>& GameSupervisor::getRobotDirection() { 
    return this-> m_robot_direction; 
}

/** @brief Retourne la liste triée des joueurs */
std::vector<Player*>& GameSupervisor::getSortedPlayers() { 
    return this-> m_sorted_players; 
}

/** @brief Retourne la cible actuellement active */
Target* GameSupervisor::getCurrentTarget() const { 
    return this-> m_current_target; 
}

/** @brief Retourne la liste des cibles */
std::vector<Target*>* GameSupervisor::getTargetsList() { 
    return this->m_targets_list; 
}

