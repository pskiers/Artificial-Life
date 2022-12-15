#include "map.h"

Field *Map::get_field( const unsigned int x_axis, const unsigned int y_axis ) {
    return &m_fields[(x_axis-1)*y_axis + y_axis];
}

Map::Map(const unsigned int height, const unsigned int width) :
        m_height( height ), m_width( width ), m_fields( height*width ) {}

// this is temporary function that will be replaced with iterator over class
std::vector<Field> *Map::getPositions() {
    return &m_fields;
}

unsigned int Map::getHeight() {
    return m_height;
}

unsigned int Map::getWidth() {
    return m_width;
}