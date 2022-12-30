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
