#include "../include/game.h"


Game::Game( const unsigned int carnivores_amount,
            const unsigned int herbivores_amount,
            const unsigned int map_height,
            const unsigned int map_width ): m_carnivore_amount(carnivores_amount), m_herbivore_amount(herbivores_amount), m_map(map_height, map_width) {
    // TODO add carnivores and herbivores to vectors
    // TODO spawn random plants on the board
    // TODO assign specimens to their starting fields
}