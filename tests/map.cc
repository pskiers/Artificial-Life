#include "map.h"
#include "field.h"
#include <gtest/gtest.h>

TEST( MapTest, MapCreation ) {
    Map map(5,10);
    EXPECT_EQ( map.getHeight(), 5);
    EXPECT_EQ( map.getWidth(), 10);
}

TEST( MapTest, MapGetField ) {
    Map map(5,10);
    Field *ptr_field = map.get_field_by_idx(5);
    EXPECT_FALSE( ptr_field->has_plant() );
    ptr_field->add_plant();
    Field *ptr_field_again = map.get_field_by_idx(5);
    EXPECT_TRUE( ptr_field_again->has_plant() );
}
