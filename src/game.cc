#include "game.h"

#include <numeric>
#include <random>


Game::Game( const unsigned int carnivores_amount,
            const unsigned int herbivores_amount,
            const unsigned int plants_amount,
            const unsigned int map_height,
            const unsigned int map_width ):
    m_carnivore_amount( carnivores_amount ),
    m_herbivore_amount( herbivores_amount ), m_plants_amount( plants_amount ), m_map( map_height, map_width ) {
    generate_population( carnivores_amount, herbivores_amount, plants_amount, map_height, map_width );
}

Game::~Game() {
    for ( auto &i : m_population ) {
        delete i;
    }
}


Map & Game::get_map() {
    return this->m_map;
}

void Game::play() {
    for (auto& specimen : this->m_population) {
        char x_diff, y_diff;
        switch (specimen->get_direction())
        {
        case NORTH:
            x_diff = 0;
            y_diff = 1;
            break;

        case NORTH_EAST:
            x_diff = 1;
            y_diff = 1;
            break;

        case EAST:
            x_diff = 1;
            y_diff = 0;
            break;

        case SOUTH_EAST:
            x_diff = 1;
            y_diff = -1;
            break;

        case SOUTH:
            x_diff = 0;
            y_diff = -1;
            break;

        case SOUTH_WEST:
            x_diff = -1;
            y_diff = -1;
            break;

        case WEST:
            x_diff = -1;
            y_diff = 0;
            break;

        case NORTH_WEST:
            x_diff = -1;
            y_diff = 1;
            break;
        }
        unsigned int prev_x = specimen->get_x_pos();
        unsigned int prev_y = specimen->get_y_pos();
        if (this->m_map.get_field(prev_x + x_diff, prev_y + y_diff)) {
            this->m_map.get_field(prev_x + x_diff, prev_y + y_diff)->set_resident(specimen);
            m_map.get_field(prev_x, prev_y)->set_resident(nullptr);
            specimen->set_x_pos(prev_x + x_diff);
            specimen->set_y_pos(prev_y + y_diff);
        }
    }
}

unsigned int Game::get_random_position( unsigned int vector_size ) {
    std::random_device random_device;
    std::mt19937 generator( random_device() );
    std::uniform_int_distribution<> distribution( 0, vector_size - 1 );
    return distribution( generator );
}

void Game::generate_population( unsigned int carnivores_amount,
                                unsigned int herbivores_amount,
                                unsigned int plants_amount,
                                unsigned int map_height,
                                unsigned int map_width ) {
    std::vector<int> positions_list( map_height * map_width );
    std::iota( std::begin( positions_list ), std::end( positions_list ), 0 );

    for ( unsigned int i = 0; i < carnivores_amount; i++ ) {
        unsigned int index = get_random_position( positions_list.size() );
        m_population.push_back( new Carnivore( positions_list[index] % map_width, positions_list[index] / map_width, 1, 1, 1, 1 ) );
        m_map.get_field_by_idx( positions_list[index] )->set_resident( m_population.back() );
        positions_list.erase( positions_list.begin() + index );
    }

    for ( unsigned int i = 0; i < herbivores_amount; i++ ) {
        unsigned int index = get_random_position( positions_list.size() );
        m_population.push_back( new Herbivore( positions_list[index] % map_width, positions_list[index] / map_width, 1, 1, 1, 1 ) );
        m_map.get_field_by_idx( positions_list[index] )->set_resident( m_population.back() );
        positions_list.erase( positions_list.begin() + index );
    }

    for ( unsigned int i = 0; i < plants_amount; i++ ) {
        unsigned int index = get_random_position( positions_list.size() );
        m_map.get_field_by_idx( positions_list[index] )->update_plant_state();
        positions_list.erase( positions_list.begin() + index );
    }
}
