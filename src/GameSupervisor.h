#pragma once

/**
 * @file GameSupervisor.h
 * @brief Déclaration de la classe GameSupervisor qui gère le déroulement du jeu : états, joueurs, robots et cibles.
 */

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

/**
 * @class GameSupervisor
 * @brief Classe qui supervise le jeu, gère les états, les joueurs, les robots et les cibles.
 */
class GameSupervisor{

private : 
    // Attributs
    Board* m_board ;
    std::vector<Player> m_players;
    std::map<Player* , int> m_announced_moves;
    std::map<Player* , int> m_real_movements_counter;
    std::pair<Robot*, Direction> m_robot_direction;
    std::vector<Player*> m_sorted_players;
    Target* m_current_target; 
    std::vector<Target*>* m_targets_list;
    enum State m_actual_state = State::INIT_PLAYERS;

public:
    /**
     * @brief Constructeur de GameSupervisor
     * Initialise un nouveau plateau, place les cibles et prépare le jeu.
     */
    GameSupervisor();
    
    /**
     * @brief Définit un plateau de jeu
     * @param i_board Plateau de jeu à utiliser
     */
    void setBoard(Board i_board);

    /**
     * @brief Initialise les joueurs à partir d'une chaîne de caractères
     * @param i_players_names Chaîne contenant les identifiants des joueurs (ex : "ABCD")
     */
    void initPlayers(std::string i_players_names);

    /**
     * @brief Enregistre le nombre de coups annoncés par un joueur
     * @param i_player Pointeur vers le joueur
     * @param i_number Nombre de coups annoncés
     */
    void announceNb(Player* i_player,const int& i_number);

    /**
     * @brief Gère le changement d'état du jeu
     * @param i_actual_state Nouvel état à appliquer
     */
    void changeState(enum State i_actual_state);

    /**
     * @brief Attribue un point au joueur
     * @param i_player Référence vers le joueur à qui ajouter un point
     */
    void givePoint(Player & i_player);

    /**
     * @brief Trie les joueurs selon les coups annoncés (ordre croissant)
     */
    void sortPlayers();

    /**
     * @brief Trouve un robot selon sa couleur
     * @param i_robots Vecteur contenant les robots disponibles
     * @param i_color Couleur du robot recherché
     * @return Pointeur vers le robot correspondant, ou nullptr s'il n'est pas trouvé
     */
    Robot* findRobotByColor(std::vector<Robot>* i_robots, const RColor& i_color);


    // Setters
    /** @brief Définit l'état actuel du jeu */
    void  setActualState(const enum State& i_actual_state);

    /** @brief Définit la liste des joueurs */
    void  setPlayers(const std::vector<Player>& i_player);

    /** @brief Définit la cible actuellement active */
    void  setCurrentTarget(Target* i_current_target);

    /** @brief Définit la direction et le robot à déplacer */
    void  setRobotDirection(const std::pair<Robot*, Direction>& i_robot_direction);

    /** @brief Définit l'ordre des joueurs pour un tour */
    void  setSortedPlayers(const std::vector<Player*>& i_sorted_players);

    /** @brief Définit les compteurs de mouvements réels */
    void  setRealMovementsCounter(const std::map<Player*, int>& i_compteur_coups_reels);

    /** @brief Définit les coups annoncés pour chaque joueur */
    void  setAnnouncedMoves(const std::map<Player*, int>& i_announced_moves);

    /** @brief Définit la liste des cibles */
    void  setTargetsList(std::vector<Target*>* i_targets_list);

    // Getters

    /** @brief Retourne l'état actuel du jeu */
    enum State getActualState();

    /** @brief Retourne le plateau de jeu */
    Board* getBoard();

    /** @brief Retourne la liste des joueurs */
    std::vector<Player>& getPlayers();
    
    /** @brief Retourne la map des coups annoncés */
    std::map<Player*, int>& getAnnouncedMoves();
    
    /** @brief Retourne la map des coups réellement effectués */
    std::map<Player*, int>& getRealMovementsCounter();

    /** @brief Retourne le robot et la direction choisis */
    std::pair<Robot*, Direction>& getRobotDirection();

    /** @brief Retourne la liste des joueurs triés */
    std::vector<Player*>& getSortedPlayers();
    
    /** @brief Retourne la cible active */
    Target* getCurrentTarget() const;
    
    /** @brief Retourne la liste des cibles */
    std::vector<Target*>* getTargetsList();
    
};