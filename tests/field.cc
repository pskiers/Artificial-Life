#include <gtest/gtest.h>
#include "field.h"


TEST(FieldTest, FieldCreation) {
  Field field;

  EXPECT_FALSE(field.has_plant());
  EXPECT_EQ(field.get_specimen(), nullptr);
}

TEST(FieldTest, FieldPlantSetting) {
  Field field;

  EXPECT_FALSE(field.has_plant());
  EXPECT_EQ(field.get_specimen(), nullptr);

  field.update_plant_state();

  EXPECT_TRUE(field.has_plant());
}
