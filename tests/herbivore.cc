#include "herbivore.h"
#include <gtest/gtest.h>

TEST( HerbivoreTest, HerbivoreDescribe ) {
    Herbivore herbivore(5,5,5,5,5,5);
    EXPECT_EQ( herbivore.describeMyself(), "Roślinożerca");
}

TEST( HerbivoreTest, HerbivoreGetters ) {
    Herbivore herbivore(1,2,3,5,6,7);
    EXPECT_EQ( herbivore.get_sight_angle(), 6);
    EXPECT_EQ( herbivore.get_sight_range(), 5);
    EXPECT_EQ( herbivore.get_time_to_sleep(), 7);
    EXPECT_EQ( herbivore.get_speed(), 3);
    EXPECT_EQ( herbivore.get_x_pos(), 1);
    EXPECT_EQ( herbivore.get_y_pos(), 2);
}