#include "herbivore.h"

Herbivore::Herbivore( unsigned int x_pos,
                      unsigned int y_pos,
                      unsigned int speed,
                      unsigned int sight_range,
                      unsigned int sight_angle,
                      unsigned int time_to_sleep ):
    Specimen( x_pos, y_pos, speed, sight_range, sight_angle, time_to_sleep ) {}

std::string Herbivore::describeMyself() {
    return "Roślinożerca";
}

std::string Herbivore::get_brush_color() {
    return "blue";
}


Direction Herbivore::get_direction( std::optional<std::tuple<unsigned int, unsigned int>> &closest_plant,
                                    std::optional<std::tuple<unsigned int, unsigned int>> &closest_herb,
                                    std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn ) {

    unsigned int herb_prio = 0, plant_prio = 0, carn_prio = 0;

    if ( !closest_plant.has_value() && !closest_herb.has_value() && !closest_carn.has_value() ) {
        std::random_device dev;
        std::mt19937 rng( dev() );
        auto distribution = std::uniform_int_distribution(static_cast<int>(NORTH), static_cast<int>(NORTH_WEST));
        return static_cast<Direction>( distribution(rng) );
    }
    if ( closest_plant.has_value() ) {
        if (max_hunger_ <= 0){
            herb_prio = 100000;
        }
        else {
            plant_prio = 1 + distance_to( closest_plant.value() ) * 5 * current_hunger_ / max_hunger_;
        }
    }

    if ( closest_herb.has_value() ) {
        if ( max_hunger_ - current_hunger_ > 20 ) {
            herb_prio = distance_to( closest_herb.value() );
        }
    }

    if ( closest_carn.has_value() ) {
        carn_prio = 200 / distance_to( closest_carn.value() );
    }

    if ( carn_prio >= herb_prio && carn_prio >= plant_prio ) {
        Direction dir = vector_to_direction( x_pos_ - std::get<0>( closest_carn.value() ),
                                             y_pos_ - std::get<1>( closest_carn.value() ) );
        orientation_ = direction_to_orientation( dir );
        return dir;
    } else if ( plant_prio >= herb_prio ) {
        Direction dir = vector_to_direction( std::get<0>( closest_plant.value() ) - x_pos_,
                                             std::get<1>( closest_plant.value() ) - y_pos_ );
        orientation_ = direction_to_orientation( dir );
        return dir;
    } else {
        Direction dir = vector_to_direction( std::get<0>( closest_herb.value() ) - x_pos_,
                                             std::get<1>( closest_herb.value() ) - y_pos_ );
        orientation_ = direction_to_orientation( dir );
        return dir;
    }
}

CollideAction Herbivore::collide_with( Specimen *other ) {
    CollideAction act = other->accept_collide( this );
    if ( act == CROSS ) {
        current_hunger_ += 8;
    }
    return act;
}

CollideAction Herbivore::accept_collide( Carnivore *other ) {
    UNUSED( other );
    return EAT;
}

CollideAction Herbivore::accept_collide( Herbivore *other ) {
    UNUSED( other );
    current_hunger_ += 8;
    return CROSS;
}

Specimen *Herbivore::cross( Specimen *other ) {
    std::random_device dev;
    std::mt19937 rng( dev() );
    auto distribution = std::uniform_real_distribution(0.0, 1.0);
    auto distribution_mut = std::normal_distribution(100000.0, 5.0);

    unsigned int speed = (distribution(rng) > 0.5) ? speed_ : other->get_speed();
    auto mut = round(distribution_mut(rng));
    unsigned int pos_mut = (mut > 0) ? static_cast<unsigned int> (mut) : 0;
    speed = (speed + pos_mut > 100000) ? speed + pos_mut - 100000 : 0;

    unsigned int sight_range = (distribution(rng) > 0.5) ? sight_range_ : other->get_sight_range();
    mut = round(distribution_mut(rng));
    pos_mut = (mut > 0) ? static_cast<unsigned int> (mut) : 0;
    sight_range = (sight_range + pos_mut > 100000) ? sight_range + pos_mut - 100000 : 0;

    unsigned int sight_angle = (distribution(rng) > 0.5) ? sight_angle_ : other->get_sight_angle();
    mut = round(distribution_mut(rng));
    pos_mut = (mut > 0) ? static_cast<unsigned int> (mut) : 0;
    sight_angle = (sight_angle + pos_mut > 100000) ? sight_angle + pos_mut - 100000 : 0;

    unsigned int time_to_sleep = (distribution(rng) > 0.5) ? time_to_sleep_ : other->get_time_to_sleep();
    mut = round(distribution_mut(rng));
    pos_mut = (mut > 0) ? static_cast<unsigned int> (mut) : 0;
    time_to_sleep = (time_to_sleep + pos_mut > 100000) ? time_to_sleep + pos_mut - 100000 : 0;

    return new Herbivore( x_pos_, y_pos_, speed, sight_range, sight_angle, time_to_sleep );
}

unsigned int Herbivore::change_carnivores_number( unsigned int current_carnivores, unsigned int change ) {
    UNUSED( change );
    return current_carnivores;
}

unsigned int Herbivore::change_herbivores_number( unsigned int current_herbivores, unsigned int change ) {
    return current_herbivores + change;
}

bool Herbivore::accept_plant() {
    if ( current_hunger_ < PLANT_VALUE ) {
        current_hunger_ = 0;
    } else {
        current_hunger_ -= PLANT_VALUE;
    }
    return true;
}
