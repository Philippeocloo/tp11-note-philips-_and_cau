#include <gtest/gtest.h>
#include "Robot.h"
#include "Board.h"
#include "enums/Direction.h"

TEST(RobotTest, ConstructorTest) {

    Cell cell = Cell(5, 3);
    Robot robot(RColor::RED, &cell);

    // Vérifier les attributs après construction
    EXPECT_EQ(robot.getColor(), RColor::RED);
    EXPECT_EQ(robot.getCell()->getX(), 5);
    EXPECT_EQ(robot.getCell()->getY(), 3);
}

TEST(RobotTest, MovementDirectionTest) {
    Board board; 

    board.initializeCells();
    board.initializeRobots();

    Robot robot = board.getRobots()->at(0); 

    int x_start = robot.getCell()->getX();
    int y_start = robot.getCell()->getY();

    // Déplacement vers la droite
    EXPECT_FALSE(robot.checkIfObstacle(Direction::RIGHT, &board));
    robot.move(Direction::RIGHT, &board);
    int x_after_right = robot.getCell()->getX();
    int y_after_right = robot.getCell()->getY();

    EXPECT_GT(x_after_right, x_start);  // X a augmenté
    EXPECT_EQ(y_after_right, y_start);  // Y inchangé

    // Déplacement vers le bas
    EXPECT_FALSE(robot.checkIfObstacle(Direction::DOWN, &board));
    robot.move(Direction::DOWN, &board);
    int x_after_down = robot.getCell()->getX();
    int y_after_down = robot.getCell()->getY();

    EXPECT_EQ(x_after_down, x_after_right); // X inchangé
    EXPECT_LT(y_after_down, y_after_right); // Y a augmenté
}


