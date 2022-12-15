#include "game.h"

#include <gtest/gtest.h>


TEST( GameTest, GameCreation ) {
    ASSERT_NO_THROW( Game game( 12, 12, 128, 128 ) );
}