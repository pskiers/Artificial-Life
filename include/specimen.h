#ifndef SPECIMEN_H
#define SPECIMEN_H

#include "field.h"

#include <iostream>
#include <string>

enum Direction {
  NORTH,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST
};


class Specimen {
  public:
    Specimen( unsigned int x_pos,
              unsigned int y_pos,
              unsigned int speed,
              unsigned int sight_range,
              unsigned int sight_angle,
              unsigned int time_to_sleep ):

        m_x_pos( x_pos ),
        m_y_pos( y_pos ),
        m_speed( speed ), m_sight_range( sight_range ), m_sight_angle( sight_angle ), m_time_to_sleep( time_to_sleep ),
        m_max_time_to_sleep( time_to_sleep ), m_current_hunger( 0 ) {
        m_max_hunger = countMaximalHunger( speed, sight_range, sight_angle, time_to_sleep );
    }
    virtual ~Specimen() = default;
    virtual void describeMyself() = 0;
    virtual std::string get_brush_color() = 0;
    virtual Direction get_direction() = 0;
    unsigned int get_x_pos();
    unsigned int get_y_pos();
    void set_x_pos(const unsigned int new_x);
    void set_y_pos(const unsigned int new_y);

  private:
    static unsigned int countMaximalHunger( unsigned int speed,
                                            unsigned int sight_range,
                                            unsigned int sight_angle,
                                            unsigned int time_to_sleep );
    unsigned int m_x_pos, m_y_pos, m_speed, m_sight_range, m_sight_angle, m_time_to_sleep, m_max_time_to_sleep, m_current_hunger,
        m_max_hunger;
};

#endif
