#include "game.h"

#include <gtest/gtest.h>


TEST( GameTest, GameCreation ) {
    ASSERT_NO_THROW( Game game( 12, 12, 12, 128, 128 ) );
}

TEST( GameTest, GameSpecimenAmount ) {
    Game game(3,3,3,5,5);

    EXPECT_EQ( game.get_carnivores_amount(), 3 );
    EXPECT_EQ( game.get_herbivores_amount(), 3 );
    EXPECT_EQ( game.get_plants_amount(), 3 );
}

TEST( GameTest, GetMapProperites ) {
    Game game(3,3,3,5,5);
    EXPECT_EQ( game.get_map().getHeight(), 3);
    EXPECT_EQ( game.get_map().getWidth(), 3);
}