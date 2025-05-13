#include <gtest/gtest.h>
#include "Player.h"
#include "Board.h"

TEST(PlayerTest, ConstructorTest) {
    Player player('A');

    EXPECT_EQ(player.getLetter(), 'A');
    EXPECT_EQ(player.getScore(), 0);
    EXPECT_TRUE(player.getBuzzer());
}

TEST(PlayerTest, SettersAndGettersTest) {
    Player player('A');

    player.setScore(10);
    EXPECT_EQ(player.getScore(), 10);

    player.setBuzzer(false);
    EXPECT_FALSE(player.getBuzzer());

    player.setScore(15);
    EXPECT_EQ(player.getScore(), 15);
}
