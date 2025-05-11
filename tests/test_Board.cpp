#include <gtest/gtest.h>
#include "../src/Board.h"
#include "../src/Cell.h"
#include "../src/Target.h"
#include "../src/enums/Border.h"
#include "../src/enums/Color.h"
#include "../src/enums/Shape.h"

TEST(BoardTest, InitializeCells) {
    Board board;
    board.initializeCells();

    // Vérifie que toutes les cellules sont initialisées
    for (int y = 0; y < TAILLE_Y; ++y) {
        for (int x = 0; x < TAILLE_X; ++x) {
            Cell& cell = board.getCell(x, y);
            EXPECT_EQ(cell.getX(), x);
            EXPECT_EQ(cell.getY(), y);
            EXPECT_EQ(cell.getBorder(), Border::NONE);
        }
    }
}

TEST(BoardTest, PlaceAngles) {
    Board board;
    board.initializeCells();
    board.placeAngles();

    // Vérifie que les angles sont placés avec des bordures et des cibles
    EXPECT_EQ(board.getCell(7, 7).getBorder(), Border::SW);
    EXPECT_EQ(board.getCell(8, 7).getBorder(), Border::SE);
    EXPECT_EQ(board.getCell(7, 8).getBorder(), Border::NW);
    EXPECT_EQ(board.getCell(8, 8).getBorder(), Border::NE);

    // Vérifie qu'il n'y a pas de cibles dans les cellules des angles du centre
    EXPECT_TRUE(!board.getCell(7, 7).hasTarget());
    EXPECT_TRUE(!board.getCell(8, 7).hasTarget());
    EXPECT_TRUE(!board.getCell(7, 8).hasTarget());
    EXPECT_TRUE(!board.getCell(8, 8).hasTarget());
}



