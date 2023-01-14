#ifndef GAME_H
#define GAME_H

#include "carnivore.h"
#include "herbivore.h"
#include "map.h"

#include <iostream>
#include <list>

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
    static unsigned int get_random_position( unsigned int vector_size );
    static std::tuple<int, int>
    calculate_angle_point( unsigned int x, unsigned int y, unsigned int angle, double distance );
    unsigned int m_carnivore_amount, m_herbivore_amount, m_plants_amount;
    std::list<Specimen *> m_population;    // iterator stability after erase needed
    Map m_map;
};

#endif
