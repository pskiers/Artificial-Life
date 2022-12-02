#ifndef SPECIMEN_H
#define SPECIMEN_H

#include "./field.h"
#include "./map.h"

class Specimen {
  public:
    Specimen( Field *position, unsigned int speed, unsigned int sight_range, unsigned int sight_angle ):
        position_( position ), speed_( speed ), sight_range_( sight_range ), sight_angle_( sight_angle % 360 ),
        food_requirements_( 0 ) {}
    ~Specimen();
    virtual void move( Map map );

  protected:
    Field *position_;
    unsigned int speed_, sight_range_, sight_angle_, food_requirements_;
};

#endif