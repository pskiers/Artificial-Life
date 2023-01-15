#include "map.h"

Field *Map::get_field_by_idx( const unsigned int index ) {
    return &fields_[index];
}
// this is temporary function that will be replaced with iterator over class

Field *Map::get_field( const unsigned int width, const unsigned int height ) {
    if ( width >= width_ || height >= height_ ) {
        return nullptr;
    }
    return &fields_[width + width_ * height];
}

Map::Map( const unsigned int height, const unsigned int width ):
    height_( height ), width_( width ), fields_( height * width ) {}

unsigned int Map::getHeight() {
    return height_;
}

unsigned int Map::getWidth() {
    return width_;
}