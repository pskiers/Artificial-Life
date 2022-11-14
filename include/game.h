#ifndef GAME_H
#define GAME_H

#include <carnivore.h>
#include <herbivore.h>
#include <map.h>
#include <vector>

class Game {
  public:
    Game( const unsigned int carnivores_amount,
          const unsigned int herbivores_amount,
          const unsigned int map_height,
          const unsigned int map_width );
    ~Game();

  private:
    unsigned int carnivore_amount_, herbivore_amount_;
    std::vector<Carnivore> carnivores_;
    std::vector<Herbivore> herbivores_;
    Map map_;
};

#endif