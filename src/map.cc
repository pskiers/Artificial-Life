#include "map.h"

Field *Map::get_field( const unsigned int index) {
    return &m_fields[index];
}

Map::Map(const unsigned int height, const unsigned int width) :
        m_height( height ), m_width( width ), m_fields( height*width ) {}

// this is temporary function that will be replaced with iterator over class
unsigned int Map::getHeight() {
    return m_height;
}

unsigned int Map::getWidth() {
    return m_width;
}