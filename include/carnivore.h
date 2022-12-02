#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "specimen.h"

const float SPEED_TO_FOOD_RATIO = 0.4;
const float SIGHT_RANGE_TO_FOOD_RATIO = 0.4;
const float SIGHT_ANGLE_TO_FOOD_RATIO = 0.4;

class Carnivore: public Specimen {

  public:
    Carnivore( Field *position, unsigned int speed, unsigned int sight_range, unsigned int sight_angle ):
        Specimen( position, speed, sight_range, sight_angle ) {
        food_requirements_ = SPEED_TO_FOOD_RATIO * speed + SIGHT_RANGE_TO_FOOD_RATIO + sight_range +
                             SIGHT_ANGLE_TO_FOOD_RATIO * sight_angle;
    }
    ~Carnivore();
};

#endif