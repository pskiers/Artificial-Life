#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "specimen.h"

class Herbivore: public Specimen {
  public:
    Herbivore( unsigned int x_pos,
               unsigned int y_pos,
               unsigned int speed,
               unsigned int sight_range,
               unsigned int sight_angle,
               unsigned int time_to_sleep );
    std::string describeMyself() override;
    std::string get_brush_color() override;
    Direction get_direction() override;
};

#endif
