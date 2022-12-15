#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "specimen.h"

class Herbivore: public Specimen {

  public:
    Herbivore( Field *position,
               unsigned int speed,
               unsigned int sight_range,
               unsigned int sight_angle,
               unsigned int time_to_sleep ):
        Specimen( position, speed, sight_range, sight_angle, time_to_sleep ) {}
};

#endif
