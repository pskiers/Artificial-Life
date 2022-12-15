#include <numeric>
#include <random>
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
    for(unsigned int i=0; i<m_map.getHeight(); i++)
    {
        for(unsigned int j = 0; j<m_map.getWidth(); j++)
        {
            if(m_map.get_field((i*m_map.getWidth())+j)->get_specimen())
            {
                m_map.get_field((i*m_map.getWidth())+j)->get_specimen()->describeMyself();
            }
            else{
                std::cout << "X:" << i << " Y:" << j << " ";
            }
        }
        std::cout << "\n";
    }
    for(unsigned int i = 0; i < m_map.getWidth()*m_map.getHeight(); i++)
    {
        if(m_map.get_field(i)->get_specimen()) {
            m_map.get_field(i)->get_specimen()->describeMyself();
            std::cout << "index: " << i << "\n";
        }
    }
}

unsigned int Game::get_random_position(unsigned int vector_size) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, vector_size - 1);
    return distribution(generator);
}

void Game::generate_population(unsigned int carnivores_amount, unsigned int herbivores_amount,
                               unsigned int plants_amount, unsigned int map_height, unsigned int map_width) {
    std::vector<int> positions_list(map_height * map_width);
    std::iota (std::begin(positions_list), std::end(positions_list), 0);

    for(unsigned int i = 0; i < carnivores_amount; i++)
    {
        unsigned int index = get_random_position(positions_list.size());
        m_population.push_back(new Carnivore(m_map.get_field(positions_list[index]), 1, 1, 1, 1));
        m_map.get_field(positions_list[index])->set_resident(m_population.back());
        positions_list.erase(positions_list.begin() + index);
    }

    for (unsigned int i = 0; i < herbivores_amount; i++)
    {
        unsigned int index = get_random_position(positions_list.size());
        m_population.push_back(new Herbivore(m_map.get_field(positions_list[index]), 1, 1, 1, 1) );
        m_map.get_field(positions_list[index])->set_resident(m_population.back());
        positions_list.erase(positions_list.begin() + index);
    }

    for (unsigned int i = 0; i < plants_amount; i++)
    {
        unsigned int index = get_random_position(positions_list.size());
        m_map.get_field(positions_list[index])->update_plant_state();
        positions_list.erase(positions_list.begin() + index);

    }

}
