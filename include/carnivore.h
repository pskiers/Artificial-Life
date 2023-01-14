#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "specimen.h"

const unsigned int HERBIVORE_VALUE = 5;

class Carnivore: public Specimen {
  public:
    Carnivore( unsigned int x_pos,
               unsigned int y_pos,
               unsigned int speed,
               unsigned int sight_range,
               unsigned int sight_angle,
               unsigned int time_to_sleep );
    std::string describeMyself() override;
    std::string get_brush_color() override;
    virtual Direction get_direction( std::optional<std::tuple<unsigned int, unsigned int>> &closest_plant,
                                     std::optional<std::tuple<unsigned int, unsigned int>> &closest_herb,
                                     std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn,
                                     bool edbe_is_visible ) override;
    Specimen *cross( Specimen *other ) override;
    CollideAction collide_with( Specimen *other ) override;
    CollideAction accept_collide( Carnivore *other ) override;
    CollideAction accept_collide( Herbivore *other ) override;
    unsigned int change_carnivores_number( unsigned int current_carnivores, unsigned int change ) override;
    unsigned int change_herbivores_number( unsigned int current_herbivores, unsigned int change ) override;
    bool accept_plant() override;
};

#endif
