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
                                    std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn,
                                    bool edge_is_visible ) {
    UNUSED( closest_plant );
    unsigned int herb_prio = 0, carn_prio = 0;
    if (!closest_herb.has_value() && !closest_carn.has_value() && edge_is_visible) {
        switch (orientation_to_direction(m_orientation))
        {
        case NORTH:
            m_orientation = direction_to_orientation(SOUTH);
            return SOUTH;

        case NORTH_EAST:
            m_orientation = direction_to_orientation(SOUTH_WEST);
            return SOUTH_WEST;

        case EAST:
            m_orientation = direction_to_orientation(WEST);
            return WEST;

        case SOUTH_EAST:
            m_orientation = direction_to_orientation(NORTH_WEST);
            return NORTH_WEST;

        case SOUTH:
            m_orientation = direction_to_orientation(NORTH);
            return NORTH;

        case SOUTH_WEST:
            m_orientation = direction_to_orientation(NORTH_EAST);
            return NORTH_EAST;

        case WEST:
            m_orientation = direction_to_orientation(EAST);
            return EAST;

        case NORTH_WEST:
            m_orientation = direction_to_orientation(SOUTH_EAST);
            return SOUTH_EAST;
        case STAY:
            return orientation_to_direction(m_orientation);
        }
    }
    if (!closest_herb.has_value() && !closest_carn.has_value()) {
        switch (orientation_to_direction(m_orientation))
        {
        case NORTH:
            m_orientation = direction_to_orientation(NORTH_EAST);
            return NORTH_EAST;

        case NORTH_EAST:
            m_orientation = direction_to_orientation(EAST);
            return EAST;

        case EAST:
            m_orientation = direction_to_orientation(SOUTH_EAST);
            return SOUTH_EAST;

        case SOUTH_EAST:
            m_orientation = direction_to_orientation(SOUTH);
            return SOUTH;

        case SOUTH:
            m_orientation = direction_to_orientation(SOUTH_WEST);
            return SOUTH_WEST;

        case SOUTH_WEST:
            m_orientation = direction_to_orientation(WEST);
            return WEST;

        case WEST:
            m_orientation = direction_to_orientation(NORTH_WEST);
            return NORTH_WEST;

        case NORTH_WEST:
            m_orientation = direction_to_orientation(NORTH);
            return NORTH;
        case STAY:
            return orientation_to_direction(m_orientation);
        }
    }

    if (closest_herb.has_value()) {
        herb_prio = 1 + distance_to(closest_herb.value()) * 20 * m_current_hunger / m_max_hunger;
    }

    if (closest_carn.has_value()) {
        if (m_max_hunger - m_current_hunger > 20) {
            carn_prio = distance_to(closest_carn.value());
        }
    }

    if (carn_prio < herb_prio) {
        Direction dir = vector_to_direction(std::get<0>(closest_herb.value()) - m_x_pos, std::get<1>(closest_herb.value()) - m_y_pos);
        m_orientation = direction_to_orientation(dir);
        return dir;
    }
    else {
        Direction dir = vector_to_direction(std::get<0>(closest_carn.value()) - m_x_pos, std::get<1>(closest_carn.value()) - m_y_pos);
        m_orientation = direction_to_orientation(dir);
        return dir;
    }
}

CollideAction Carnivore::collide_with( Specimen *other ) {
    CollideAction action = other->accept_collide( this );
    if ( action == EAT ) {
        if ( m_current_hunger < HERBIVORE_VALUE ) {
            m_current_hunger = 0;
        } else {
            m_current_hunger -= HERBIVORE_VALUE;
        }
    }
    else if (action == CROSS) {
        m_current_hunger += 8;
    }
    return action;
}

CollideAction Carnivore::accept_collide( Carnivore *other ) {
    UNUSED( other );
    m_current_hunger += 8;
    return CROSS;
}

CollideAction Carnivore::accept_collide( Herbivore *other ) {
    UNUSED( other );
    return STOP;
}

Specimen *Carnivore::cross( Specimen *other ) {
    UNUSED( other );
    // TODO actually cross
    return new Carnivore( m_x_pos, m_y_pos, m_speed, m_sight_range, m_sight_angle, m_time_to_sleep );
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
