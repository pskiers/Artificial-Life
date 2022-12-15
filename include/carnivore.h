#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "specimen.h"

class Carnivore: public Specimen {

  public:
    Carnivore( Field *position,
               unsigned int speed,
               unsigned int sight_range,
               unsigned int sight_angle,
               unsigned int time_to_sleep ):
        Specimen( position, speed, sight_range, sight_angle, time_to_sleep ) {}
};

#endif
