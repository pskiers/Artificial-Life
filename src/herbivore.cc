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


Direction Herbivore::get_direction() {
    return SOUTH_EAST;
}

CollideAction Herbivore::collide_with(Specimen *other) {
    return other->accept_collide(this);
}

CollideAction Herbivore::accept_collide(Carnivore *other) {
    UNUSED(other);
    return STOP;
}

CollideAction Herbivore::accept_collide(Herbivore *other) {
    UNUSED(other);
    return CROSS;
}

Specimen* Herbivore::cross(Specimen *other) {
    //TODO actually cross
    UNUSED(other);
    return new Herbivore(
        m_x_pos,
        m_y_pos,
        m_speed,
        m_sight_range,
        m_sight_angle,
        m_time_to_sleep
    );
}

unsigned int Herbivore::change_carnivores_number(unsigned int current_carnivores, unsigned int change) {
    UNUSED(change);
    return current_carnivores;
}

unsigned int Herbivore::change_herbivores_number(unsigned int current_herbivores, unsigned int change) {
    return current_herbivores + change;
}
