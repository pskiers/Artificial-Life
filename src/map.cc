#include "../include/map.h"

std::optional<Field &> Map::get_field( const unsigned int x, const unsigned int y ) {
    if ( x > this->height_ || y > this->width_ )
        return std::optional<Field &>();
    return this->fields_[x][y];
}