#ifndef SPECIMEN_H
#define SPECIMEN_H
#define UNUSED( expr )  \
    do {                \
        (void)( expr ); \
    } while ( 0 )

#include "field.h"

#include <iostream>
#include <optional>
#include <string>
#include <tuple>

const unsigned int ZERO_HUNGER_SIGHT_RANGE = 90;
const unsigned int ZERO_HUNGER_SIGHT_ANGLE = 90;
const unsigned int ZERO_HUNGER_SLEEP = 10;

enum Direction { NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST, STAY };
enum CollideAction { EAT, CROSS, STOP };

class Carnivore;
class Herbivore;

class Specimen {
  public:
    Specimen( unsigned int x_pos,
              unsigned int y_pos,
              unsigned int speed,
              unsigned int sight_range,
              unsigned int sight_angle,
              unsigned int time_to_sleep ):

        m_x_pos( x_pos ),
        m_y_pos( y_pos ), m_speed( speed ), m_sight_range( sight_range ), m_sight_angle( sight_angle ),
        m_time_to_sleep( time_to_sleep ), m_max_time_to_sleep( time_to_sleep ), m_current_hunger( 0 ),
        m_time_to_next_move( speed ), m_orientation( 0 ) {
        m_max_hunger = countMaximalHunger( speed, sight_range, sight_angle, time_to_sleep );
    }
    virtual ~Specimen() = default;
    virtual std::string describeMyself() = 0;
    virtual std::string get_brush_color() = 0;
    virtual Direction get_direction( std::optional<std::tuple<unsigned int, unsigned int>> &closest_plant,
                                     std::optional<std::tuple<unsigned int, unsigned int>> &closest_herb,
                                     std::optional<std::tuple<unsigned int, unsigned int>> &closest_carn ) = 0;
    virtual Specimen *cross( Specimen *other ) = 0;

    // Should be used like this: A moves and walks into B = A.collide_with(B)
    virtual CollideAction collide_with( Specimen *other ) = 0;
    virtual CollideAction accept_collide( Carnivore *other ) = 0;
    virtual CollideAction accept_collide( Herbivore *other ) = 0;
    virtual unsigned int change_carnivores_number( unsigned int current_carnivores, unsigned int change ) = 0;
    virtual unsigned int change_herbivores_number( unsigned int current_herbivores, unsigned int change ) = 0;
    virtual bool accept_plant() = 0;

    bool starved_to_death();
    bool can_move();
    unsigned int get_x_pos();
    unsigned int get_y_pos();
    unsigned int get_speed();
    unsigned int get_sight_range();
    unsigned int get_sight_angle();
    unsigned int get_time_to_sleep();
    unsigned int get_max_time_to_sleep();
    unsigned int get_current_hunger();
    unsigned int get_max_hunger();
    unsigned int get_orientation();
    void set_x_pos( const unsigned int new_x );
    void set_y_pos( const unsigned int new_y );

  private:
    static unsigned int countMaximalHunger( unsigned int speed,
                                            unsigned int sight_range,
                                            unsigned int sight_angle,
                                            unsigned int time_to_sleep );

  protected:
    unsigned int m_x_pos, m_y_pos, m_speed, m_sight_range, m_sight_angle, m_time_to_sleep, m_max_time_to_sleep,
        m_current_hunger, m_max_hunger, m_time_to_next_move, m_orientation;
};

#endif
