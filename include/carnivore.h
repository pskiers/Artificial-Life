#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "specimen.h"

const unsigned int HERBIVORE_VALUE = 20;
const unsigned int CRITICAL_HERBIVORE_VALUE = 100000;
const unsigned int CARN_HUNGER_RATIO = 20;
const unsigned int CARN_IGNORE_CROSSING_HUNGER = 20;
const unsigned int CARN_CROSSING_COST = 15;
const double CARN_MUTATION_VARIATION = 5.0;

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
                                     std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn ) override;
    Specimen *cross( Specimen *other ) override;
    CollideAction collide_with( Specimen *other ) override;
    CollideAction accept_collide( Carnivore *other ) override;
    CollideAction accept_collide( Herbivore *other ) override;
    unsigned int change_carnivores_number( unsigned int current_carnivores, unsigned int change ) override;
    unsigned int change_herbivores_number( unsigned int current_herbivores, unsigned int change ) override;
    bool accept_plant() override;
};

#endif
