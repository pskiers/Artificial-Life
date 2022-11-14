#ifndef MAP_H
#define MAP_H

#include "field.h"

#include <optional>
#include <vector>

class Map {
  public:
    Map( const unsigned int height, const unsigned int width ):
        height_( height ), width_( width ), fields_( height, std::vector<Field>( width ) ) {}
    ~Map();
    std::optional<Field &> get_field( const unsigned int x, const unsigned int y );

  private:
    unsigned int height_, width_;
    std::vector<std::vector<Field>> fields_;
};

#endif