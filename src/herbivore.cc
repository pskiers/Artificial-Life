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
    if (!closest_plant.has_value() && !closest_herb.has_value() && !closest_carn.has_value()) {
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
    if (closest_plant.has_value()) {
        plant_prio = 1 + distance_to(closest_plant.value()) * 5 * m_current_hunger / m_max_hunger;
    }

    if (closest_herb.has_value()) {
        if (m_max_hunger - m_current_hunger > 20) {
            herb_prio = distance_to(closest_herb.value());
        }
    }

    if (closest_carn.has_value()) {
        carn_prio = 200 / distance_to(closest_carn.value());
    }

    if (carn_prio >= herb_prio && carn_prio >= plant_prio) {
        Direction dir = vector_to_direction(m_x_pos - std::get<0>(closest_carn.value()), m_y_pos - std::get<1>(closest_carn.value()));
        m_orientation = direction_to_orientation(dir);
        return dir;
    }
    else if (plant_prio >= herb_prio) {
        Direction dir = vector_to_direction(std::get<0>(closest_plant.value()) - m_x_pos, std::get<1>(closest_plant.value()) - m_y_pos);
        m_orientation = direction_to_orientation(dir);
        return dir;
    }
    else {
        Direction dir = vector_to_direction(std::get<0>(closest_herb.value()) - m_x_pos, std::get<1>(closest_herb.value()) - m_y_pos);
        m_orientation = direction_to_orientation(dir);
        return dir;
    }
}

CollideAction Herbivore::collide_with( Specimen *other ) {
    CollideAction act = other->accept_collide( this );
    if (act == CROSS) {
        m_current_hunger += 8;
    }
    return act;
}

CollideAction Herbivore::accept_collide( Carnivore *other ) {
    UNUSED( other );
    return EAT;
}

CollideAction Herbivore::accept_collide( Herbivore *other ) {
    UNUSED( other );
    m_current_hunger += 8;
    return CROSS;
}

Specimen *Herbivore::cross( Specimen *other ) {
    // TODO actually cross
    UNUSED( other );
    return new Herbivore( m_x_pos, m_y_pos, m_speed, m_sight_range, m_sight_angle, m_time_to_sleep );
}

unsigned int Herbivore::change_carnivores_number( unsigned int current_carnivores, unsigned int change ) {
    UNUSED( change );
    return current_carnivores;
}

unsigned int Herbivore::change_herbivores_number( unsigned int current_herbivores, unsigned int change ) {
    return current_herbivores + change;
}

bool Herbivore::accept_plant() {
    if ( m_current_hunger < PLANT_VALUE ) {
        m_current_hunger = 0;
    } else {
        m_current_hunger -= PLANT_VALUE;
    }
    return true;
}
