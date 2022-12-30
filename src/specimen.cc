#include "specimen.h"

unsigned int Specimen::countMaximalHunger( unsigned int speed,
                                           unsigned int sight_range,
                                           unsigned int sight_angle,
                                           unsigned int time_to_sleep ) {
    return speed + sight_range + sight_angle + time_to_sleep;
}

unsigned int Specimen::get_x_pos() {
    return this->m_x_pos;
}

unsigned int Specimen::get_y_pos() {
    return this->m_y_pos;
}

void Specimen::set_x_pos( const unsigned int new_x ) {
    this->m_x_pos = new_x;
}

void Specimen::set_y_pos( const unsigned int new_y ) {
    this->m_y_pos = new_y;
}
