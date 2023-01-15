#include "carnivore.h"

Carnivore::Carnivore( unsigned int x_pos,
                      unsigned int y_pos,
                      unsigned int speed,
                      unsigned int sight_range,
                      unsigned int sight_angle,
                      unsigned int time_to_sleep ):
    Specimen( x_pos, y_pos, speed, sight_range, sight_angle, time_to_sleep ) {}

std::string Carnivore::describeMyself() {
    return "Mięsożerca";
}

std::string Carnivore::get_brush_color() {
    return "red";
}

Direction Carnivore::get_direction( std::optional<std::tuple<unsigned int, unsigned int>> &closest_plant,
                                    std::optional<std::tuple<unsigned int, unsigned int>> &closest_herb,
                                    std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn ) {
    UNUSED( closest_plant );
    unsigned int herb_prio = 0, carn_prio = 0;

    if ( closest_herb.has_value() ) {
        if ( max_hunger_ <= 0 ) {
            herb_prio = CRITICAL_HERBIVORE_VALUE;
        } else {
            herb_prio = 1 + distance_to( closest_herb.value() ) * CARN_HUNGER_RATIO * current_hunger_ / max_hunger_;
        }
    }

    if ( closest_carn.has_value() ) {
        if ( max_hunger_ - current_hunger_ > CARN_IGNORE_CROSSING_HUNGER ) {
            carn_prio = distance_to( closest_carn.value() );
        }
    }

    if ( carn_prio == 0 && herb_prio == 0 ) {
        std::random_device dev;
        std::mt19937 rng( dev() );
        auto distribution = std::uniform_int_distribution( static_cast<int>( NORTH ), static_cast<int>( NORTH_WEST ) );
        return static_cast<Direction>( distribution( rng ) );
    }

    if ( carn_prio < herb_prio ) {
        Direction dir = vector_to_direction( std::get<0>( closest_herb.value() ) - x_pos_,
                                             std::get<1>( closest_herb.value() ) - y_pos_ );
        orientation_ = direction_to_orientation( dir );
        return dir;
    } else {
        Direction dir = vector_to_direction( std::get<0>( closest_carn.value() ) - x_pos_,
                                             std::get<1>( closest_carn.value() ) - y_pos_ );
        orientation_ = direction_to_orientation( dir );
        return dir;
    }
}

CollideAction Carnivore::collide_with( Specimen *other ) {
    CollideAction action = other->accept_collide( this );
    if ( action == EAT ) {
        if ( current_hunger_ < HERBIVORE_VALUE ) {
            current_hunger_ = 0;
        } else {
            current_hunger_ -= HERBIVORE_VALUE;
        }
    } else if ( action == CROSS ) {
        current_hunger_ += CARN_CROSSING_COST;
    }
    return action;
}

CollideAction Carnivore::accept_collide( Carnivore *other ) {
    UNUSED( other );
    current_hunger_ += CARN_CROSSING_COST;
    return CROSS;
}

CollideAction Carnivore::accept_collide( Herbivore *other ) {
    UNUSED( other );
    return STOP;
}

Specimen *Carnivore::cross( Specimen *other ) {
    std::random_device dev;
    std::mt19937 rng( dev() );
    auto distribution = std::uniform_real_distribution( 0.0, 1.0 );

    const unsigned int safe_scaler = 100000;
    auto distribution_mut = std::normal_distribution( static_cast<double>( safe_scaler ), CARN_MUTATION_VARIATION );

    unsigned int speed = ( distribution( rng ) > 0.5 ) ? speed_ : other->get_speed();
    auto mut = round( distribution_mut( rng ) );
    unsigned int pos_mut = ( mut > 0 ) ? static_cast<unsigned int>( mut ) : 0;
    speed = ( speed + pos_mut > safe_scaler ) ? speed + pos_mut - safe_scaler : 0;

    unsigned int sight_range = ( distribution( rng ) > 0.5 ) ? sight_range_ : other->get_sight_range();
    mut = round( distribution_mut( rng ) );
    pos_mut = ( mut > 0 ) ? static_cast<unsigned int>( mut ) : 0;
    sight_range = ( sight_range + pos_mut > safe_scaler ) ? sight_range + pos_mut - safe_scaler : 0;

    unsigned int sight_angle = ( distribution( rng ) > 0.5 ) ? sight_angle_ : other->get_sight_angle();
    mut = round( distribution_mut( rng ) );
    pos_mut = ( mut > 0 ) ? static_cast<unsigned int>( mut ) : 0;
    sight_angle = ( sight_angle + pos_mut > safe_scaler ) ? sight_angle + pos_mut - safe_scaler : 0;

    unsigned int time_to_sleep = ( distribution( rng ) > 0.5 ) ? time_to_sleep_ : other->get_time_to_sleep();
    mut = round( distribution_mut( rng ) );
    pos_mut = ( mut > 0 ) ? static_cast<unsigned int>( mut ) : 0;
    time_to_sleep = ( time_to_sleep + pos_mut > safe_scaler ) ? time_to_sleep + pos_mut - safe_scaler : 0;

    return new Carnivore( x_pos_, y_pos_, speed, sight_range, sight_angle, time_to_sleep );
}

unsigned int Carnivore::change_carnivores_number( unsigned int current_carnivores, unsigned int change ) {
    return current_carnivores + change;
}

unsigned int Carnivore::change_herbivores_number( unsigned int current_herbivores, unsigned int change ) {
    UNUSED( change );
    return current_herbivores;
}

bool Carnivore::accept_plant() {
    return false;
}
