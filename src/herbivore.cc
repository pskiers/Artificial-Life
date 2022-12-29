#include "herbivore.h"

Herbivore::Herbivore( unsigned int x_pos,
                      unsigned int y_pos,
                      unsigned int speed,
                      unsigned int sight_range,
                      unsigned int sight_angle,
                      unsigned int time_to_sleep ):
    Specimen( x_pos, y_pos, speed, sight_range, sight_angle, time_to_sleep ) {}

void Herbivore::describeMyself() {
    std::cout << "Cattle  ";
}

std::string Herbivore::get_brush_color() {
    return "blue";
}


Direction Herbivore::get_direction() {
    return NORTH;
}
