#ifndef GAME_H
#define GAME_H

#include "carnivore.h"
#include "herbivore.h"
#include "map.h"

#include <vector>
#include <iostream>

class Game {
  public:
    Game( unsigned int carnivores_amount,
          unsigned int herbivores_amount,
          unsigned int plants_amount,
          unsigned int map_height,
          unsigned int map_width );
    ~Game();
    void play();

  private:
    void generate_population(unsigned int carnivores_amount, unsigned int  herbivores_amount,
                             unsigned int plants_amount, unsigned int  map_height, unsigned int map_width);
    static unsigned int get_random_position(unsigned int vector_size);
    unsigned int m_carnivore_amount, m_herbivore_amount, m_plants_amount;
    std::vector<Specimen*> m_population;
    Map m_map;
};

#endif
