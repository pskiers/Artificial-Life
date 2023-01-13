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


Direction Carnivore::get_direction() {
    return NORTH_WEST;
}

CollideAction Carnivore::collide_with(Specimen *other) {
    CollideAction action = other->accept_collide(this);
    if (action == EAT) {
        if (m_current_hunger < HERBIVORE_VALUE) {
            m_current_hunger = 0;
        }
        else {
            m_current_hunger -= HERBIVORE_VALUE;
        }
    }
    return action;
}

CollideAction Carnivore::accept_collide(Carnivore *other) {
    UNUSED(other);
    return CROSS;
}

CollideAction Carnivore::accept_collide(Herbivore *other) {
    UNUSED(other);
    return STOP;
}

Specimen* Carnivore::cross(Specimen *other) {
    UNUSED(other);
    //TODO actually cross
    return new Carnivore(
        m_x_pos,
        m_y_pos,
        m_speed,
        m_sight_range,
        m_sight_angle,
        m_time_to_sleep
    );
}

unsigned int Carnivore::change_carnivores_number(unsigned int current_carnivores, unsigned int change) {
    return current_carnivores + change;
}

unsigned int Carnivore::change_herbivores_number(unsigned int current_herbivores, unsigned int change) {
    UNUSED(change);
    return current_herbivores;
}

bool Carnivore::accept_plant() {
    return false;
}
