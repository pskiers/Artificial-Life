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
                                    std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn,
                                    bool edge_is_visible ) {

    unsigned int herb_prio = 0, plant_prio = 0, carn_prio = 0;
    if ( !closest_herb.has_value() && !closest_carn.has_value() && edge_is_visible ) {
        switch ( orientation_to_direction( orientation_ ) ) {
            case NORTH:
                orientation_ = direction_to_orientation( SOUTH );
                return SOUTH;

            case NORTH_EAST:
                orientation_ = direction_to_orientation( SOUTH_WEST );
                return SOUTH_WEST;

            case EAST:
                orientation_ = direction_to_orientation( WEST );
                return WEST;

            case SOUTH_EAST:
                orientation_ = direction_to_orientation( NORTH_WEST );
                return NORTH_WEST;

            case SOUTH:
                orientation_ = direction_to_orientation( NORTH );
                return NORTH;

            case SOUTH_WEST:
                orientation_ = direction_to_orientation( NORTH_EAST );
                return NORTH_EAST;

            case WEST:
                orientation_ = direction_to_orientation( EAST );
                return EAST;

            case NORTH_WEST:
                orientation_ = direction_to_orientation( SOUTH_EAST );
                return SOUTH_EAST;
            case STAY:
                return orientation_to_direction( orientation_ );
        }
    }
    if ( !closest_plant.has_value() && !closest_herb.has_value() && !closest_carn.has_value() ) {
        switch ( orientation_to_direction( orientation_ ) ) {
            case NORTH:
                orientation_ = direction_to_orientation( NORTH_EAST );
                return NORTH_EAST;

            case NORTH_EAST:
                orientation_ = direction_to_orientation( EAST );
                return EAST;

            case EAST:
                orientation_ = direction_to_orientation( SOUTH_EAST );
                return SOUTH_EAST;

            case SOUTH_EAST:
                orientation_ = direction_to_orientation( SOUTH );
                return SOUTH;

            case SOUTH:
                orientation_ = direction_to_orientation( SOUTH_WEST );
                return SOUTH_WEST;

            case SOUTH_WEST:
                orientation_ = direction_to_orientation( WEST );
                return WEST;

            case WEST:
                orientation_ = direction_to_orientation( NORTH_WEST );
                return NORTH_WEST;

            case NORTH_WEST:
                orientation_ = direction_to_orientation( NORTH );
                return NORTH;
            case STAY:
                return orientation_to_direction( orientation_ );
        }
    }
    if ( closest_plant.has_value() ) {
        plant_prio = 1 + distance_to( closest_plant.value() ) * 5 * current_hunger_ / max_hunger_;
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
    // TODO actually cross
    UNUSED( other );
    return new Herbivore( x_pos_, y_pos_, speed_, sight_range_, sight_angle_, time_to_sleep_ );
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
