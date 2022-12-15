#ifndef GAME_H
#define GAME_H

#include "carnivore.h"
#include "herbivore.h"
#include "map.h"

#include <vector>

class Game {
  public:
    Game( const unsigned int carnivores_amount,
          const unsigned int herbivores_amount,
          const unsigned int map_height,
          const unsigned int map_width );
    void play();

  private:
    unsigned int m_carnivore_amount, m_herbivore_amount;
    std::vector<Specimen> m_population;
    Map m_map;
};

#endif
