#include "specimen.h"

unsigned int Specimen::countMaximalHunger( unsigned int speed,
                                           unsigned int sight_range,
                                           unsigned int sight_angle,
                                           unsigned int time_to_sleep ) {
    if ( speed + ZERO_HUNGER_SIGHT_RANGE + ZERO_HUNGER_SIGHT_ANGLE + ZERO_HUNGER_SLEEP <
         sight_range * 5 + sight_angle ) {
        return 0;
    }
    return speed + ZERO_HUNGER_SIGHT_RANGE - sight_range * 5 + ZERO_HUNGER_SIGHT_ANGLE - sight_angle +
           ZERO_HUNGER_SLEEP - time_to_sleep;
}

unsigned int Specimen::get_x_pos() {
    return this->x_pos_;
}

unsigned int Specimen::get_y_pos() {
    return this->y_pos_;
}

unsigned int Specimen::get_speed() {
    return this->speed_;
}

unsigned int Specimen::get_sight_range() {
    return this->sight_range_;
}

unsigned int Specimen::get_sight_angle() {
    return this->sight_angle_;
}

unsigned int Specimen::get_time_to_sleep() {
    return this->time_to_sleep_;
}

unsigned int Specimen::get_max_time_to_sleep() {
    return this->max_time_to_sleep_;
}

unsigned int Specimen::get_current_hunger() {
    return this->current_hunger_;
}

unsigned int Specimen::get_max_hunger() {
    return this->max_hunger_;
}

void Specimen::set_x_pos( const unsigned int new_x ) {
    this->x_pos_ = new_x;
}

void Specimen::set_y_pos( const unsigned int new_y ) {
    this->y_pos_ = new_y;
}

bool Specimen::starved_to_death() {
    if ( current_hunger_ > max_hunger_ ) {
        return true;
    }
    return false;
}

bool Specimen::can_move() {
    ++current_hunger_;

    if ( time_to_next_move_ > 0 ) {
        time_to_next_move_ -= 1;
        return false;
    }
    time_to_next_move_ = speed_;

    if ( time_to_sleep_ == 0 ) {
        time_to_sleep_ = max_time_to_sleep_;
        return false;
    }
    time_to_sleep_ -= 1;

    return true;
}

unsigned int Specimen::get_orientation() {
    return orientation_;
}

unsigned int Specimen::distance_to( std::tuple<unsigned int, unsigned int> to ) {
    unsigned int x_dist, y_dist;
    if ( x_pos_ > std::get<0>( to ) ) {
        x_dist = x_pos_ - std::get<0>( to );
    } else {
        x_dist = std::get<0>( to ) - x_pos_;
    }
    if ( y_pos_ > std::get<1>( to ) ) {
        y_dist = y_pos_ - std::get<1>( to );
    } else {
        y_dist = std::get<1>( to ) - y_pos_;
    }
    if ( x_dist > y_dist ) {
        return x_dist;
    }
    return y_dist;
}

Direction Specimen::vector_to_direction( int x, int y ) {
    if ( x == 0 && y >= 0 ) {
        return SOUTH;
    } else if ( x == 0 && y < 0 ) {
        return NORTH;
    }

    if ( x >= 0 && y == 0 ) {
        return EAST;
    } else if ( x < 0 && y == 0 ) {
        return WEST;
    }

    if ( abs( x ) >= abs( y ) ) {
        double scaled_y = static_cast<double>( y ) / abs( x );
        if ( x >= 0 ) {
            if ( scaled_y >= 0.5 ) {
                return SOUTH_EAST;
            } else if ( scaled_y >= -0.5 ) {
                return EAST;
            } else {
                return NORTH_EAST;
            }
        } else {
            if ( scaled_y >= 0.5 ) {
                return SOUTH_WEST;
            } else if ( scaled_y >= -0.5 ) {
                return WEST;
            } else {
                return NORTH_WEST;
            }
        }
    } else {
        double scaled_x = static_cast<double>( x ) / abs( y );
        if ( y >= 0 ) {
            if ( scaled_x >= 0.5 ) {
                return SOUTH_EAST;
            } else if ( scaled_x >= -0.5 ) {
                return SOUTH;
            } else {
                return SOUTH_WEST;
            }
        } else {
            if ( scaled_x >= 0.5 ) {
                return NORTH_EAST;
            } else if ( scaled_x >= -0.5 ) {
                return NORTH;
            } else {
                return NORTH_WEST;
            }
        }
    }
}

unsigned int Specimen::direction_to_orientation( Direction direction ) {
    switch ( direction ) {
        case NORTH:
            return 90;

        case NORTH_EAST:
            return 45;

        case EAST:
            return 0;

        case SOUTH_EAST:
            return 315;

        case SOUTH:
            return 270;

        case SOUTH_WEST:
            return 225;

        case WEST:
            return 180;

        case NORTH_WEST:
            return 135;

        default:
            return 0;
    }
}

Direction Specimen::orientation_to_direction( unsigned int orientation ) {
    switch ( orientation ) {
        case 90:
            return NORTH;

        case 45:
            return NORTH_EAST;

        case 0:
            return EAST;

        case 315:
            return SOUTH_EAST;

        case 270:
            return SOUTH;

        case 225:
            return SOUTH_WEST;

        case 180:
            return WEST;

        case 135:
            return NORTH_WEST;

        default:
            return STAY;
    }
}


bool Specimen::operator==(const Specimen& other) {
    return x_pos_ == other.x_pos_ && y_pos_ == other.y_pos_;
}
