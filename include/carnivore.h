#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "specimen.h"

class Carnivore: public Specimen {
  public:
    Carnivore( Field *position,
               unsigned int speed,
               unsigned int sight_range,
               unsigned int sight_angle,
               unsigned int time_to_sleep );
    void describeMyself() override;
    std::string get_brush() override;
};

#endif
