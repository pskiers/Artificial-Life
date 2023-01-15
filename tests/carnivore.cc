#include "carnivore.h"
#include <gtest/gtest.h>

TEST( CarnivoreTest, CarnivoreDescribe ) {
    Carnivore carnivore(5,5,5,5,5,5);
    EXPECT_EQ( carnivore.describeMyself(), "Mięsożerca");
}

TEST( CarnivoreTest, CarnivoreGetters ) {
    Carnivore carnivore(1,2,3,5,6,7);
    EXPECT_EQ( carnivore.get_sight_angle(), 6);
    EXPECT_EQ( carnivore.get_sight_range(), 5);
    EXPECT_EQ( carnivore.get_time_to_sleep(), 7);
    EXPECT_EQ( carnivore.get_speed(), 3);
    EXPECT_EQ( carnivore.get_x_pos(), 1);
    EXPECT_EQ( carnivore.get_y_pos(), 2);
}
