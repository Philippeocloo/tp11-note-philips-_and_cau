#include <gtest/gtest.h>

#include "../src/GameSupervisor.h"
#include "../src/Cell.h"
#include "../src/Target.h"
#include "../src/Player.h"
#include "../src/Board.h"
#include "../src/Robot.h"

#include "../src/enums/Border.h"
#include "../src/enums/Color.h"
#include "../src/enums/Shape.h"


TEST(GameSupervisorTest, initPlayersTest) {
    GameSupervisor gameSupervisor;

    // Init players
    gameSupervisor.initPlayers("ABCD");

    // Verif des lettres 
    std::vector<Player> players = gameSupervisor.getPlayers();
    EXPECT_EQ(players.size(), 4);
    EXPECT_EQ(players[0].getLetter(), 'A');
    EXPECT_EQ(players[1].getLetter(), 'B');
    EXPECT_EQ(players[2].getLetter(), 'C');
    EXPECT_EQ(players[3].getLetter(), 'D');
}

TEST(GameSupervisorTest,FindRobotByColorTest) {
    // Create a GameSupervisor instance
    GameSupervisor gameSupervisor;

    // Get the robots from the board
    std::vector<Robot>* robots = gameSupervisor.getBoard()->getRobots();

    // Test finding a robot by color
    Robot* foundRobot = gameSupervisor.findRobotByColor(robots, RColor::R_RED);
    EXPECT_EQ(foundRobot->getColor(), RColor::R_RED);
}

TEST(GameSupervisorTest, GivePointTest) {
    // Creaction d'un joueur
    Player player('A');

    GameSupervisor gameSupervisor;

    // Donner un point au joueur
    gameSupervisor.givePoint(player);

    // Vérifier que le score du joueur a été mis à jour
    EXPECT_EQ(player.getScore(), 1);
}

TEST(GameSupervisorTest, SortPlayersTest) {
    // Création de joueurs
    Player player1('A');
    Player player2('B');
    Player player3('C');

    GameSupervisor gameSupervisor;

    // Ajouter les joueurs au GameSupervisor
    gameSupervisor.setPlayers({player1, player2, player3});

    //récupérer les propositions des joueurs
    gameSupervisor.announceNb(&player1, 3);
    gameSupervisor.announceNb(&player2, 1);
    gameSupervisor.announceNb(&player3, 2);

    // Tri en fonction du nombre de coups annoncés
    gameSupervisor.sortPlayers();

    // Vérifier l'ordre de passage
    std::vector<Player*> sortedPlayers = gameSupervisor.getSortedPlayers();

    EXPECT_EQ(sortedPlayers[0]->getLetter(), 'B'); // Player with 1 move
    EXPECT_EQ(sortedPlayers[1]->getLetter(), 'C'); // Player with 2 moves
    EXPECT_EQ(sortedPlayers[2]->getLetter(), 'A'); // Player with 3 moves
}

TEST(GameSupervisorTest, SettersAndGettersTest) {
    // Création d'une instance Board 
    GameSupervisor gameSupervisor;

    // Création et ajout des joueurs dans le GameSupervisor
    Player player1('A');
    Player player2('B');
    std::vector<Player> players = {player1, player2};
    gameSupervisor.setPlayers(players);
    EXPECT_EQ(gameSupervisor.getPlayers().size(), 2);

    // Set and get actual state
    gameSupervisor.setActualState(State::INIT_PLAYERS);
    EXPECT_EQ(gameSupervisor.getActualState(), State::INIT_PLAYERS);

    // Set and get current target
    Target target( Shape::CIRCLE , RColor::R_RED);
    gameSupervisor.setCurrentTarget(&target);
    EXPECT_EQ(gameSupervisor.getCurrentTarget()->getColor(), RColor::R_RED);

}