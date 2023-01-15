#include "field.h"

#include <random>

Field::Field(): has_plant_( false ), resident_( nullptr ), without_plant_( 0 ) {}

void Field::update_plant_state() {
    if ( has_plant_ ) {
        return;
    }
    std::random_device dev;
    std::mt19937 rng( dev() );
    std::uniform_real_distribution<> distribution( 0.0, 1.0 );
    auto random = distribution( rng );
    if ( random + without_plant_ * INCREASE_RATIO > THRESHOLD ) {
        has_plant_ = true;
        without_plant_ = 0;
    }
    ++without_plant_;
}

bool Field::has_plant() {
    return has_plant_;
}

void Field::add_plant() {
    has_plant_ = true;
}

void Field::remove_plant() {
    has_plant_ = false;
}

Specimen *Field::get_specimen() {
    return resident_;
}

void Field::set_resident( Specimen *new_resident ) {
    resident_ = new_resident;
    if ( new_resident && has_plant_ && new_resident->accept_plant() )
        has_plant_ = false;
}