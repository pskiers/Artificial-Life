#ifndef MAP_H
#define MAP_H

#include "field.h"

#include <vector>

class Map {
  public:
    Map( const unsigned int height, const unsigned int width ):
        m_height( height ), m_width( width ), m_fields( height, std::vector<Field>( width ) ) {}
    Field *get_field( const unsigned int x, const unsigned int y );

  private:
    unsigned int m_height, m_width;
    std::vector<std::vector<Field>> m_fields;
};

#endif
