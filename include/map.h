#ifndef MAP_H
#define MAP_H

#include "field.h"

#include <vector>

class Map {
  public:
    Map( unsigned int height, unsigned int width );
    Field *get_field( unsigned int x_axis, unsigned int y_axis );
    std::vector<Field>* getPositions();
    unsigned int getHeight();
    unsigned int getWidth();

  private:
    unsigned int m_height, m_width;
    std::vector<Field> m_fields;
};

#endif
