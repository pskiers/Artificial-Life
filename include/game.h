#ifndef GAME_H
#define GAME_H

#include "carnivore.h"
#include "herbivore.h"
#include "map.h"

#include <iostream>
#include <list>

const unsigned int INIT_MAX_SPEED = 3;
const unsigned int INIT_MIN_SPEED = 0;
const unsigned int INIT_MAX_SIGHT_RANGE = 7;
const unsigned int INIT_MIN_SIGHT_RANGE = 2;
const unsigned int INIT_MAX_SIGHT_ANGLE = 120;
const unsigned int INIT_MIN_SIGHT_ANGLE = 30;
const unsigned int INIT_MAX_SLEEP = 8;
const unsigned int INIT_MIN_SLEEP = 1;

class Game {
  public:
    Game( unsigned int carnivores_amount,
          unsigned int herbivores_amount,
          unsigned int plants_amount,
          unsigned int map_height,
          unsigned int map_width );
    ~Game();
    void play();
    Map &get_map();
    unsigned int get_carnivores_amount();
    unsigned int get_herbivores_amount();
    unsigned int get_plants_amount();

  private:
    void generate_population( unsigned int carnivores_amount,
                              unsigned int herbivores_amount,
                              unsigned int plants_amount,
                              unsigned int map_height,
                              unsigned int map_width );
    static unsigned int get_random_position( unsigned int vector_size, std::mt19937 &generator );
    static std::tuple<int, int>
    calculate_angle_point( unsigned int x, unsigned int y, unsigned int angle, double distance );

    unsigned int carnivore_amount_;
    unsigned int herbivore_amount_;
    unsigned int plants_amount_;
    std::list<Specimen *> population_;    // iterator stability after erase needed
    Map map_;
};

#endif
