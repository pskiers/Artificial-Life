#include "../include/game.h"


Game::Game( const unsigned int carnivores_amount,
            const unsigned int herbivores_amount,
            const unsigned int map_height,
            const unsigned int map_width ): carnivore_amount_(carnivores_amount), herbivore_amount_(herbivores_amount), map_(map_height, map_width) {
    // TODO add carnivores and herbivores to vectors
    // TODO spawn random plants on the board
    // TODO assign specimens to their starting fields
}