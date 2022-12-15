#include <gtest/gtest.h>
#include "game.h"


TEST(GameTest, GameCreation) {
  ASSERT_NO_THROW(Game game(12, 12, 128, 128));
}