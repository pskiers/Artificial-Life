#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "specimen.h"

class Herbivore: public Specimen {
  public:
    Herbivore( Field *position,
               unsigned int speed,
               unsigned int sight_range,
               unsigned int sight_angle,
               unsigned int time_to_sleep );
    void describeMyself() override;
};

#endif
