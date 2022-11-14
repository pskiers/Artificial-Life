#include "../include/field.h"


void Field::update_plant_state() {
    // TODO maybe add some probability of plants growing back, maybe probability should be dependant on the time this
    // field has been without plants
    this->has_plants_ = true;
}