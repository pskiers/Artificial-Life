#include "field.h"
#include "carnivore.h"
#include "specimen.h"
#include <gtest/gtest.h>


TEST( FieldTest, FieldCreation ) {
    Field field;

    EXPECT_FALSE( field.has_plant() );
    EXPECT_EQ( field.get_specimen(), nullptr );
}

TEST( FieldTest, FieldPlantSetting ) {
    Field field;

    EXPECT_FALSE( field.has_plant() );
    EXPECT_EQ( field.get_specimen(), nullptr );

    field.add_plant();

    EXPECT_TRUE( field.has_plant() );
}

TEST( FieldTest, FieldAddRemoveSetting ) {
    Field field;

    EXPECT_FALSE( field.has_plant() );
    field.add_plant();
    EXPECT_TRUE( field.has_plant() );
    field.remove_plant();
    EXPECT_FALSE( field.has_plant() );
}

TEST( FieldTest, FieldAddSpecimen ) {
    Field field;
    Carnivore carnivore(1,1,1,1,1,1);
    Carnivore* ptr_spec = &carnivore;
    field.set_resident(ptr_spec);
    EXPECT_EQ(field.get_specimen(), dynamic_cast<Specimen*>(ptr_spec));
}
