#include "game.h"

#include <algorithm>
#include <numeric>
#include <optional>
#include <random>
#include <tuple>


Game::Game( const unsigned int carnivores_amount,
            const unsigned int herbivores_amount,
            const unsigned int plants_amount,
            const unsigned int map_height,
            const unsigned int map_width ):
    carnivore_amount_( carnivores_amount ),
    herbivore_amount_( herbivores_amount ), plants_amount_( plants_amount ), map_( map_height, map_width ) {
    generate_population( carnivores_amount, herbivores_amount, plants_amount, map_height, map_width );
}

Game::~Game() {
    for ( auto &i : population_ ) {
        delete i;
    }
}


Map &Game::get_map() {
    return this->map_;
}

unsigned int Game::get_carnivores_amount() {
    return this->carnivore_amount_;
}

unsigned int Game::get_herbivores_amount() {
    return this->herbivore_amount_;
}

unsigned int Game::get_plants_amount() {
    return this->plants_amount_;
}

std::tuple<int, int>
Game::calculate_angle_point( unsigned int x, unsigned int y, unsigned int angle, double distance ) {
    if ( angle <= 45 || angle > 315 ) {
        x += distance;
        y += round( distance * tan( angle * M_PI / 180 ) );
    } else if ( angle == 90 ) {
        x += 0;
        y += distance;
    } else if ( 45 < angle && angle <= 135 ) {
        y += distance;
        x += round( distance / tan( angle * M_PI / 180 ) );
    } else if ( 135 < angle && angle <= 225 ) {
        x -= distance;
        y -= round( distance * tan( angle * M_PI / 180 ) );
    } else if ( angle == 270 ) {
        x += 0;
        y -= distance;
    } else if ( 225 < angle && angle <= 315 ) {
        y -= distance;
        x -= round( distance / tan( angle * M_PI / 180 ) );
    }
    return std::tuple<unsigned int, unsigned int> { x, y };
}

void Game::play() {
    std::list<Specimen *> to_add_next;
    for ( auto iter = this->population_.begin(); iter != this->population_.end(); ++iter ) {
        Specimen *specimen = *iter;
        if ( specimen->starved_to_death() ) {
            iter = population_.erase( iter );
            map_.get_field( specimen->get_x_pos(), specimen->get_y_pos() )->set_resident( nullptr );
            herbivore_amount_ = specimen->change_herbivores_number( herbivore_amount_, -1 );
            carnivore_amount_ = specimen->change_carnivores_number( carnivore_amount_, -1 );
            delete specimen;
            continue;
        }

        if ( !specimen->can_move() ) {
            continue;
        }
        unsigned int prev_x = specimen->get_x_pos();
        unsigned int prev_y = specimen->get_y_pos();

        std::optional<std::tuple<unsigned int, unsigned int>> closest_plant, closest_carn, closest_herb;

        double distance = 1;
        while ( distance <= specimen->get_sight_range() ) {
            unsigned int angle_l = ( specimen->get_orientation() + specimen->get_sight_angle() + 360 ) % 360;
            unsigned int angle_r = ( specimen->get_orientation() - specimen->get_sight_angle() + 360 ) % 360;

            std::tuple<int, int> l_point = calculate_angle_point( prev_x, prev_y, angle_l, distance );
            std::tuple<int, int> r_point = calculate_angle_point( prev_x, prev_y, angle_r, distance );
            Field *field;
            if ( std::get<0>( l_point ) < 0 || std::get<1>( l_point ) < 0 ) {
                field = nullptr;
            } else {
                field = map_.get_field( static_cast<unsigned int>( std::get<0>( l_point ) ),
                                        static_cast<unsigned int>( std::get<1>( l_point ) ) );
            }
            if ( field ) {
                if ( !closest_plant.has_value() ) {
                    if ( field->has_plant() ) {
                        closest_plant = l_point;
                    }
                }
                Specimen *resident = field->get_specimen();
                if ( resident ) {
                    if ( resident->describeMyself() == "Mięsożerca" ) {
                        if ( !closest_carn.has_value() ) {
                            closest_carn = l_point;
                        }
                    } else {
                        if ( !closest_herb.has_value() ) {
                            closest_herb = l_point;
                        }
                    }
                }
            }
            while ( l_point != r_point ) {
                if ( std::get<0>( l_point ) < prev_x + distance && std::get<1>( l_point ) == prev_y + distance ) {
                    ++std::get<0>( l_point );
                } else if ( std::get<0>( l_point ) == prev_x + distance &&
                            std::get<1>( l_point ) > prev_y - distance ) {
                    --std::get<1>( l_point );
                } else if ( std::get<0>( l_point ) > prev_x - distance &&
                            std::get<1>( l_point ) == prev_y - distance ) {
                    --std::get<0>( l_point );
                } else if ( std::get<0>( l_point ) == prev_x - distance &&
                            std::get<1>( l_point ) < prev_y + distance ) {
                    ++std::get<1>( l_point );
                }

                if ( std::get<0>( l_point ) < 0 || std::get<1>( l_point ) < 0 ) {
                    field = nullptr;
                } else {
                    field = map_.get_field( static_cast<unsigned int>( std::get<0>( l_point ) ),
                                            static_cast<unsigned int>( std::get<1>( l_point ) ) );
                }
                Field *field = map_.get_field( std::get<0>( l_point ), std::get<1>( l_point ) );
                if ( field ) {
                    if ( !closest_plant.has_value() ) {
                        if ( field->has_plant() ) {
                            closest_plant = l_point;
                        }
                    }
                    Specimen *resident = field->get_specimen();
                    if ( resident ) {
                        if ( resident->describeMyself() == "Mięsożerca" ) {
                            if ( !closest_carn.has_value() ) {
                                closest_carn = l_point;
                            }
                        } else {
                            if ( !closest_herb.has_value() ) {
                                closest_herb = l_point;
                            }
                        }
                    }
                }
            }

            ++distance;
        }


        char x_diff = 0, y_diff = 0;
        switch ( specimen->get_direction( closest_plant, closest_herb, closest_carn ) ) {
            case NORTH:
                x_diff = 0;
                y_diff = -1;
                break;

            case NORTH_EAST:
                x_diff = 1;
                y_diff = -1;
                break;

            case EAST:
                x_diff = 1;
                y_diff = 0;
                break;

            case SOUTH_EAST:
                x_diff = 1;
                y_diff = 1;
                break;

            case SOUTH:
                x_diff = 0;
                y_diff = 1;
                break;

            case SOUTH_WEST:
                x_diff = -1;
                y_diff = 1;
                break;

            case WEST:
                x_diff = -1;
                y_diff = 0;
                break;

            case NORTH_WEST:
                x_diff = -1;
                y_diff = -1;
                break;
            case STAY:
                x_diff = 0;
                y_diff = 0;
                break;
        }
        if ( x_diff == 0 && y_diff == 0 ) {
            continue;
        }

        Field *destination_field = this->map_.get_field( prev_x + x_diff, prev_y + y_diff );
        if ( destination_field ) {
            Specimen *destination_specimen = destination_field->get_specimen();
            if ( destination_specimen ) {
                CollideAction action = specimen->collide_with( destination_specimen );
                bool in_to_add = false;
                switch ( action ) {
                    case EAT:
                        for ( auto iter2 = to_add_next.begin(); iter2 != to_add_next.end(); ++iter2 ) {
                            if ( **iter2 == *destination_specimen ) {
                                to_add_next.erase( iter2 );
                                in_to_add = true;
                                break;
                            }
                        }
                        if ( !in_to_add ) {
                            for ( auto iter2 = this->population_.begin(); iter2 != this->population_.end(); ++iter2 ) {
                                if ( **iter2 == *destination_specimen ) {
                                    this->population_.erase( iter2 );
                                    break;
                                }
                            }
                        }
                        delete destination_specimen;
                        herbivore_amount_ -= 1;

                        destination_field->set_resident( specimen );
                        map_.get_field( prev_x, prev_y )->set_resident( nullptr );
                        specimen->set_x_pos( prev_x + x_diff );
                        specimen->set_y_pos( prev_y + y_diff );
                        break;

                    case CROSS:
                        for ( int i = -1; i < 2; ++i ) {
                            for ( int j = -1; j < 2; ++j ) {
                                Field *kid_field = this->map_.get_field( prev_x + x_diff + i, prev_y + y_diff + j );
                                if ( kid_field && !kid_field->get_specimen() ) {
                                    Specimen *kid = specimen->cross( destination_specimen );
                                    kid_field->set_resident( kid );
                                    to_add_next.push_back( kid );
                                    kid->set_x_pos( prev_x + x_diff + i );
                                    kid->set_y_pos( prev_y + y_diff + j );
                                    herbivore_amount_ = kid->change_herbivores_number( herbivore_amount_, 1 );
                                    carnivore_amount_ = kid->change_carnivores_number( carnivore_amount_, 1 );
                                    i = 2;
                                    j = 2;
                                }
                            }
                        }
                        break;

                    case STOP:
                        break;
                }
            } else {
                destination_field->set_resident( specimen );
                map_.get_field( prev_x, prev_y )->set_resident( nullptr );
                specimen->set_x_pos( prev_x + x_diff );
                specimen->set_y_pos( prev_y + y_diff );
            }
        }
    }

    for ( auto new_specimen : to_add_next ) {
        if ( !new_specimen ) {
            continue;
        }
        if ( map_.get_field( new_specimen->get_x_pos(), new_specimen->get_y_pos() )->get_specimen() == new_specimen ) {
            population_.push_back( new_specimen );
        }
    }

    unsigned int plant_nr = 0;
    for ( unsigned int i = 0; i < map_.getHeight(); ++i ) {
        for ( unsigned int j = 0; j < map_.getWidth(); ++j ) {
            map_.get_field( j, i )->update_plant_state();
            if ( map_.get_field( j, i )->has_plant() ) {
                ++plant_nr;
            }
        }
    }
    plants_amount_ = plant_nr;
}

unsigned int Game::get_random_position( unsigned int vector_size, std::mt19937 &generator ) {
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

    std::random_device random_device;
    std::mt19937 generator( random_device() );
    std::uniform_int_distribution<> speed_dist( INIT_MIN_SPEED, INIT_MAX_SPEED );
    std::uniform_int_distribution<> sight_range_dist( INIT_MIN_SIGHT_RANGE, INIT_MAX_SIGHT_RANGE );
    std::uniform_int_distribution<> sight_angle_dist( INIT_MIN_SIGHT_ANGLE, INIT_MAX_SIGHT_ANGLE );
    std::uniform_int_distribution<> sleep_dist( INIT_MIN_SLEEP, INIT_MAX_SLEEP );

    for ( unsigned int i = 0; i < carnivores_amount; ++i ) {
        unsigned int index = get_random_position( positions_list.size(), generator );
        unsigned int speed = sleep_dist( generator );
        unsigned int sight_range = sight_range_dist( generator );
        unsigned int sight_angle = sight_angle_dist( generator );
        unsigned int sleep = sleep_dist( generator );
        population_.push_back( new Carnivore( positions_list[index] % map_width,
                                              positions_list[index] / map_width,
                                              speed,
                                              sight_range,
                                              sight_angle,
                                              sleep ) );
        map_.get_field_by_idx( positions_list[index] )->set_resident( population_.back() );
        positions_list.erase( positions_list.begin() + index );
    }

    for ( unsigned int i = 0; i < herbivores_amount; ++i ) {
        unsigned int index = get_random_position( positions_list.size(), generator );
        unsigned int speed = sleep_dist( generator );
        unsigned int sight_range = sight_range_dist( generator );
        unsigned int sight_angle = sight_angle_dist( generator );
        unsigned int sleep = sleep_dist( generator );
        population_.push_back( new Herbivore( positions_list[index] % map_width,
                                              positions_list[index] / map_width,
                                              speed,
                                              sight_range,
                                              sight_angle,
                                              sleep ) );
        map_.get_field_by_idx( positions_list[index] )->set_resident( population_.back() );
        positions_list.erase( positions_list.begin() + index );
    }

    for ( unsigned int i = 0; i < plants_amount; ++i ) {
        unsigned int index = get_random_position( positions_list.size(), generator );
        map_.get_field_by_idx( positions_list[index] )->add_plant();
        positions_list.erase( positions_list.begin() + index );
    }
}
