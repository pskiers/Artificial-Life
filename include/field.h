#ifndef FIELD_H
#define FIELD_H

#include "specimen.h"

const double INCREASE_RATIO = 0.01;
const double THRESHOLD = 0.99;

class Specimen;

class Field {
  public:
    Field();
    bool has_plant();
    void update_plant_state();
    void add_plant();
    void remove_plant();
    Specimen *get_specimen();
    void set_resident( Specimen *new_resident );

  private:
    bool has_plant_;
    Specimen *resident_;
    unsigned int without_plant_;
};

#endif
