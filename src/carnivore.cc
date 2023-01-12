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
    return other->accept_collide(this);
}

CollideAction Carnivore::accept_collide(Carnivore *other) {
    UNUSED(other);
    return CROSS;
}

CollideAction Carnivore::accept_collide(Herbivore *other) {
    UNUSED(other);
    return EAT;
}

Specimen* Carnivore::cross(Specimen *other) {
    UNUSED(other);
    //TODO actually cross
    return new Carnivore(
        this->get_x_pos(),
        this->get_y_pos(),
        this->get_speed(),
        this->get_sight_range(),
        this->get_sight_angle(),
        this->get_time_to_sleep()
    );
}

unsigned int Carnivore::change_carnivores_number(unsigned int current_carnivores, unsigned int change) {
    return current_carnivores + change;
}

unsigned int Carnivore::change_herbivores_number(unsigned int current_herbivores, unsigned int change) {
    UNUSED(change);
    return current_herbivores;
}
