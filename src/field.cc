#include "../include/field.h"


void Field::update_plant_state() {
    // TODO maybe add some probability of plants growing back, maybe probability should be dependant on the time this
    // field has been without plants
    m_has_plant = true;
}

bool Field::has_plant() {
    return m_has_plant;
}

void Field::remove_plant() {
    m_has_plant = false;
}

Specimen& Field::get_specimen() {
    return m_resident;
}

void Field::set_resident(Specimen *new_resident) {
    m_resident = *new_resident;
}