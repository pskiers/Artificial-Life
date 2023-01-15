#ifndef MAP_H
#define MAP_H

#include "field.h"

#include <vector>

class Map {
  public:
    Map( unsigned int height, unsigned int width );
    Field *get_field_by_idx( const unsigned int index );
    Field *get_field( const unsigned int width, const unsigned int height );
    unsigned int getHeight();
    unsigned int getWidth();

  private:
    unsigned int height_;
    unsigned int width_;
    std::vector<Field> fields_;
};

#endif
