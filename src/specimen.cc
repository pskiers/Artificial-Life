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
    return this->m_x_pos;
}

unsigned int Specimen::get_y_pos() {
    return this->m_y_pos;
}

unsigned int Specimen::get_speed() {
    return this->m_speed;
}

unsigned int Specimen::get_sight_range() {
    return this->m_sight_range;
}

unsigned int Specimen::get_sight_angle() {
    return this->m_sight_angle;
}

unsigned int Specimen::get_time_to_sleep() {
    return this->m_time_to_sleep;
}

unsigned int Specimen::get_max_time_to_sleep() {
    return this->m_max_time_to_sleep;
}

unsigned int Specimen::get_current_hunger() {
    return this->m_current_hunger;
}

unsigned int Specimen::get_max_hunger() {
    return this->m_max_hunger;
}

void Specimen::set_x_pos( const unsigned int new_x ) {
    this->m_x_pos = new_x;
}

void Specimen::set_y_pos( const unsigned int new_y ) {
    this->m_y_pos = new_y;
}

bool Specimen::starved_to_death() {
    if ( m_current_hunger > m_max_hunger ) {
        return true;
    }
    return false;
}

bool Specimen::can_move() {
    ++m_current_hunger;

    if ( m_time_to_next_move > 0 ) {
        m_time_to_next_move -= 1;
        return false;
    }
    m_time_to_next_move = m_speed;

    if ( m_time_to_sleep == 0 ) {
        m_time_to_sleep = m_max_time_to_sleep;
        return false;
    }
    m_time_to_sleep -= 1;

    return true;
}

unsigned int Specimen::get_orientation() {
    return m_orientation;
}

unsigned int Specimen::distance_to( std::tuple<unsigned int, unsigned int> to ) {
    unsigned int x_dist, y_dist;
    if ( m_x_pos > std::get<0>( to ) ) {
        x_dist = m_x_pos - std::get<0>( to );
    } else {
        x_dist = std::get<0>( to ) - m_x_pos;
    }
    if ( m_y_pos > std::get<1>( to ) ) {
        y_dist = m_y_pos - std::get<1>( to );
    } else {
        y_dist = std::get<0>( to ) - m_y_pos;
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
