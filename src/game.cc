#include "game.h"


Game::Game( const unsigned int carnivores_amount,
            const unsigned int herbivores_amount,
            const unsigned int plants_amount,
            const unsigned int map_height,
            const unsigned int map_width ):
    m_carnivore_amount( carnivores_amount ), m_herbivore_amount( herbivores_amount ), m_plants_amount( plants_amount ),
    m_map( map_height, map_width ){
    generate_population(carnivores_amount, herbivores_amount, plants_amount, map_height, map_width);
}

Game::~Game() {
    for (auto & i : m_population)
    {
        delete i;
    }
}

void Game::play() {
    for(unsigned int i=0; i<m_map.getWidth(); i++)
        for(unsigned int j = 0; j<m_map.getHeight(); i++)
        {
            if(m_map.get_field(i,j)->get_specimen())
            {
                std::cout << "X value: " << i << " Y value: " << j << "\n";
                //m_map.get_field(i,j)->get_specimen()->describeMyself();
            }
        }
}

unsigned int Game::get_random_position(unsigned int vector_size) {
    double random = ((double) rand() / (RAND_MAX));
    auto position = (unsigned int) (random* vector_size);
    return position;
}

void Game::generate_population(unsigned int carnivores_amount, unsigned int herbivores_amount,
                               unsigned int plants_amount, unsigned int map_height, unsigned int map_width) {
    std::vector<int> positions_list(map_height * map_width);

    for(unsigned int i = 0; i < carnivores_amount; i++)
    {
        unsigned int index = get_random_position(positions_list.size());
        unsigned int x_axis = (positions_list[index]-1)%map_width;
        unsigned int y_axis = positions_list[index]/map_width - 1;
        positions_list.erase(positions_list.begin() + index);
        m_population.push_back(new Carnivore(m_map.get_field(x_axis, y_axis), 1, 1, 1, 1));
    }

    for (unsigned int i = 0; i < herbivores_amount; i++)
    {
        unsigned int index = get_random_position(positions_list.size());
        unsigned int x_axis = (positions_list[index]-1)%map_width;
        unsigned int y_axis = positions_list[index]/map_width - 1;
        positions_list.erase(positions_list.begin() + index);
        m_population.push_back(new Herbivore(m_map.get_field(x_axis, y_axis), 1, 1, 1, 1) );
    }

    for (unsigned int i = 0; i < plants_amount; i++)
    {
        unsigned int index = get_random_position(positions_list.size());
        unsigned int x_axis = (positions_list[index]-1)%map_width;
        unsigned int y_axis = positions_list[index]/map_width - 1;
        m_map.get_field(x_axis, y_axis)->update_plant_state();
    }

}
