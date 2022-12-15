#ifndef SPECIMEN_H
#define SPECIMEN_H

#include "field.h"

#include <iostream>

class Field;

class Specimen {
  public:
    Specimen( Field *position,
              unsigned int speed,
              unsigned int sight_range,
              unsigned int sight_angle,
              unsigned int time_to_sleep ):
        m_position( position ),
        m_speed( speed ), m_sight_range( sight_range ), m_sight_angle( sight_angle ), m_time_to_sleep( time_to_sleep ),
        m_max_time_to_sleep( time_to_sleep ), m_current_hunger( 0 ) {
        m_max_hunger = countMaximalHunger( speed, sight_range, sight_angle, time_to_sleep );
    }
    virtual ~Specimen() = default;
    virtual void describeMyself() = 0;

  private:
    static unsigned int countMaximalHunger( unsigned int speed,
                                            unsigned int sight_range,
                                            unsigned int sight_angle,
                                            unsigned int time_to_sleep );
    Field *m_position;
    unsigned int m_speed, m_sight_range, m_sight_angle, m_time_to_sleep, m_max_time_to_sleep, m_current_hunger,
        m_max_hunger;
};

#endif
